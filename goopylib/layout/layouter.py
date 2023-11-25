from .container import Container


def process_container(container: Container):
    assert container.parent is None
    assert container.width.unit == "px"

    container.flex.process_children(0, 0)
