from buffers import VertexBuffer, IndexBuffer


class VertexArray:
    def __init__(self, *args):
        raise NotImplementedError()

    def __repr__(self) -> str:
        raise NotImplementedError()

    def bind(self):
        raise NotImplementedError()

    def unbind(self):
        raise NotImplementedError()

    def draw(self):
        raise NotImplementedError()

    def set_index_buffer(self, *args: IndexBuffer):
        raise NotImplementedError()

    def add_vertex_buffer(self, *args: VertexBuffer):
        raise NotImplementedError()

    def get_vertex_buffers(self) -> tuple[VertexBuffer, ...]:
        raise NotImplementedError()
