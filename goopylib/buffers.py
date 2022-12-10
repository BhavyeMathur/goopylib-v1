from typing import Literal


ShaderDataType = Literal["float", "float2", "float3", "float4",
                         "mat3", "mat4",
                         "int", "int2", "int3", "int4",
                         "bool"]


class BufferElement:
    def __init__(self, name: str, dtype: ShaderDataType, normalized: bool = False):
        raise NotImplementedError()

    def __repr__(self) -> str:
        raise NotImplementedError()


class VertexBuffer():
    def __init__(self, vertices: tuple):
        raise NotImplementedError()

    def __repr__(self) -> str:
        raise NotImplementedError()

    def __len__(self) -> int:
        raise NotImplementedError()

    def bind(self):
        raise NotImplementedError()

    def unbind(self):
        raise NotImplementedError()

    @property
    def layout(self) -> tuple[BufferElement, ...]:
        raise NotImplementedError()

    @layout.setter
    def layout(self, value: tuple[BufferElement, ...]):
        raise NotImplementedError()

    @property
    def data(self) -> tuple:
        raise NotImplementedError()

    @data.setter
    def data(self, value: tuple):
        raise NotImplementedError()


class IndexBuffer:
    def __init__(self, indices: tuple[int, ...]):
        raise NotImplementedError()

    def __repr__(self) -> str:
        raise NotImplementedError()

    def __len__(self) -> int:
        raise NotImplementedError()

    def bind(self):
        raise NotImplementedError()

    def unbind(self):
        raise NotImplementedError()


from ext.buffers import *
