{{ name | replace("goopylib.objects.", "") | escape | underline }}

.. currentmodule:: {{ module }}

.. autoclass:: {{ name }}
    :members:
    :undoc-members:

{% if name == "Quad" %}
.. autoclass:: Rectangle
    :members:
    :undoc-members:
{% elif name == "Ellipse" %}
.. autoclass:: Circle
    :members:
    :undoc-members:
{% endif %}
