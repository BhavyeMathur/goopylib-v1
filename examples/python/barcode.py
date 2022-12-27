import goopylib as gp
import src.extension.archive.buffers as buffers
import src.extension.archive.shader as shader

window = gp.Window(500, 500, "Barcode")

vertex_shader = """
        #version 330 core

        layout (location = 0) in vec2 position;
        out vec2 Pos;

        void main() {
            gl_Position = vec4(position.x, position.y, 0.0f, 1.0f);
            Pos = position;
        }"""

fragment_shader = """
        #version 330 core

        out vec4 FragColor;
        in vec2 Pos;

        void main() {
            float t = 50 * Pos.x;
            FragColor = vec4(round(cos(t)), round(cos(t)), round(cos(t)), 1.0f);
        }"""

shader = shader.Shader(vertex_shader, fragment_shader)

vertex_array = buffers.VertexArray()
vertex_array.set_index_buffer(buffers.IndexBuffer(0, 1, 2,
                                                  0, 2, 3))

vertex_buffer = buffers.VertexBuffer(-0.5, -0.5,
                                     0.5, -0.5,
                                     0.5, 0.5,
                                     -0.5, 0.5)
vertex_buffer.layout = (buffers.BufferElement("vertices", "float2"),)

vertex_array.add_vertex_buffer(vertex_buffer)

while window.is_open():
    shader.bind()
    vertex_array.draw()

    gp.update()


gp.terminate()
