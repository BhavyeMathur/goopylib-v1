class Shader:
    def __init__(self, vertex_shader: str, fragment_shader: str):
        raise NotImplementedError()

    def __repr__(self):
        pass

    def bind(self):
        raise NotImplementedError()

    def unbind(self):
        raise NotImplementedError()


from ext.shader import *
