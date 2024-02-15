"""
For internal use only.
"""

from typing import NoReturn
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


def raise_(err: type, msg: str) -> NoReturn:
    """
    Raises an error. To be used with assert statements

    Args:
        err: type of Exception
        msg: Exception message
    """
    raise err(msg)


def raise_type_error(obj, expected: str) -> NoReturn:
    """
    Raises a TypeError. To be used with assert statements

    Args:
        obj: the object received
        expected: the type expected
    """
    raise TypeError(f"'{expected}' argument expected, got '{type(obj)}'")
