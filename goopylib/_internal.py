"""
For internal use only.
"""

import inspect


def convert_getset_descriptor_to_properties(cobj: type) -> None:
    """
    Converts C extension classes "getset_decriptors" to @properties

    Args:
        cobj: C extension object to act on
    """
    for var, prop in vars(cobj).items():
        if inspect.isgetsetdescriptor(prop):
            setattr(cobj, var, property(prop.__get__, prop.__set__,
                                        prop.__delete__, prop.__doc__))
