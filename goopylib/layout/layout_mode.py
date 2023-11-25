from __future__ import annotations


class _LayoutMode:
    def process_children(self, container: Container, x: int, y: int, _only_direct: bool = False) -> None:
        raise NotImplemented()

    def get_auto_width(self, container: Container) -> int:
        raise NotImplemented()

    def get_auto_height(self, container: Container) -> int:
        raise NotImplemented()


from .container import Container
