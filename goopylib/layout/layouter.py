from .container import Container


def process_container(container: Container):
    assert container.parent is None
    assert container.width.unit == "px"

    container.layout.process_children(container, 0, 0)
