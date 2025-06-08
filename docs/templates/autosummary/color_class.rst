{{ name | replace("goopylib.color.", "") | escape | underline }}

.. currentmodule:: {{ module }}

.. autoclass:: {{ name }}
    :members:
    :undoc-members:
    :inherited-members:
    :show-inheritance:
    :special-members: __add__, __sub__, {% if name == "ColorHex" %} __repr__ {% endif %}
