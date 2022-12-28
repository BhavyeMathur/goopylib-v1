from typing import Literal, Union
from vertex_array import *


class VertexBuffer:
    def __init__(self, *args: Union[tuple[float, ...], float]):
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
    def __init__(self, *args: Union[tuple[int, ...], int]):
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
