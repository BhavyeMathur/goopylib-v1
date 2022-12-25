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

    def get_count(self) -> int:
        raise NotImplementedError()
