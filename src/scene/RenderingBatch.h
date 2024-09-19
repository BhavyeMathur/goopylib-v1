#pragma once

#include "RenderingBatchBase.h"
#include "objects/Vertex.h"

namespace gp {

    class Triangle;

    class Quad;

    class Ellipse;

    class TexturedQuad;

    template<typename Object, typename VertexType, typename VertexAttribType>
        class GPAPI RenderingBatch : public RenderingBatchBase {
        public:
            RenderingBatch(BufferLayout layout, int indexIncrement, int vertexIncrement, const Shader &shader)
                    : RenderingBatchBase(layout, indexIncrement, vertexIncrement, shader) {
            }

            void drawObject(uint32_t ID, const shared_ptr<Object> &object) {
                GP_CORE_DEBUG("gp::RenderingBatch::drawObject({0})", ID);

                const uint32_t index = m_VertexData.size();
                std::cout << "Creating " << ID << std::endl;
                m_IDToIndex.insert({ID, index});

                auto vertexAttribs = static_cast<const VertexAttribType *>(object->vertexAttribData());

                for (int i = 0; i < m_VertexIncrement; i++) {
                    m_VertexData.emplace_back(object->vertexData()[i], object->getZ(), vertexAttribs[i]);

                    if (object->isHidden())
                        m_VertexData[index + i].attrib.color.alpha = 0;
                }

                m_Indices += m_IndexIncrement;
                m_Vertices += m_VertexIncrement;
                m_ReallocateBufferData = true;
                m_BufferData = m_VertexData.data();
            }

            void destroyObject(uint32_t ID) {
                std::cout << "Destroying " << ID << std::endl;
                const uint32_t index = m_IDToIndex.at(ID);

                m_VertexData.erase(std::next(m_VertexData.begin(), index),
                                   std::next(m_VertexData.begin(), index + m_VertexIncrement));
                m_IDToIndex.erase(ID);

                for (auto &i: m_IDToIndex) {
                    if (i.second > index)
                        i.second -= m_VertexIncrement;
                }

                m_Indices -= m_IndexIncrement;
                m_Vertices -= m_VertexIncrement;
                m_ReallocateBufferData = true;
                m_BufferData = m_VertexData.data();
            }

            void updateObject(uint32_t ID, const shared_ptr<Object> &object) {
                const uint32_t index = m_IDToIndex.at(ID);
                auto vertexAttribs = static_cast<const VertexAttribType *>(object->vertexAttribData());

                for (int i = 0; i < m_VertexIncrement; i++) {
                    m_VertexData[index + i] = {object->vertexData()[i], object->getZ(), vertexAttribs[i]};

                    if (object->isHidden())
                        m_VertexData[index + i].attrib.color.alpha = 0;
                }
                m_UpdateBufferData = true;
            }

        private:
            std::vector<VertexType> m_VertexData;
        };
}
