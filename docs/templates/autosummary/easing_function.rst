{{ name | replace("_", " ") | escape | underline | title()}}

.. currentmodule:: {{ module }}

{% if name != "ease_linear" %}
.. autofunction:: {{ name }}_in
.. autofunction:: {{ name }}_out
{% endif %}

.. autofunction:: {{ name }}

.. image:: ../easing_graphs/{{ name }}.png
   :align: center
