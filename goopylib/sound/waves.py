from wave import open as waveopen
from math import sin as mathsin
from struct import pack as structpack

from goopylib.sound.Sound import Sound
from goopylib.util import GraphicsError


def create_sin_wave(filename, duration, freq, tag=None, volume=1, sample_rate=7000):

    if not (isinstance(duration, float) or isinstance(duration, int)):
        raise GraphicsError(f"\n\nGraphicsError: duration value for sin wave must be an int or float, not {duration}")
    if not (isinstance(freq, int) or isinstance(freq, float)):
        raise GraphicsError(f"\n\nGraphicsError: freq value for sin wave must be an int or float, not {freq}")

    if not (isinstance(volume, float) or isinstance(volume, int)):
        raise GraphicsError(f"\n\nGraphicsError: volume for sin wave must be a float or int, not {volume}")
    if not (0 <= volume <= 1):
        raise GraphicsError(f"\n\nGraphicsError: volume for sin wave must be between 0 & 1, not {volume}")

    if not (isinstance(sample_rate, float) or isinstance(sample_rate, int)):
        raise GraphicsError(f"\n\nGraphicsError: sample rate for sin wave must be an integer or float,"
                            f" not {sample_rate}")

    audio = []
    num_samples = int(duration * sample_rate)

    scale = 6.283 * (freq / sample_rate)
    volume *= 127.5
    for x in range(num_samples):
        audio.append(volume * mathsin(x * scale))

    return create_sound_from_values(filename, audio, tag=tag, channels=1, sample_rate=sample_rate)


def create_sawtooth_wave(filename, duration, freq, reverse=False, tag=None, volume=1, sample_rate=7000):
    
    if not (isinstance(duration, float) or isinstance(duration, int)):
        raise GraphicsError(f"\n\nGraphicsError: duration value for sawtooth wave must be an int or float, not {duration}")
    if not (isinstance(volume, float) or isinstance(volume, int)):
        raise GraphicsError(f"\n\nGraphicsError: volume for sawtooth wave must be a float or int, not {volume}")
    if not (0 <= volume <= 1):
        raise GraphicsError(f"\n\nGraphicsError: volume for sawtooth wave must be between 0 & 1, not {volume}")

    if not (isinstance(sample_rate, float) or isinstance(sample_rate, int)):
        raise GraphicsError(f"\n\nGraphicsError: sample rate for sawtooth wave must be an integer or float,"
                            f" not {sample_rate}")
    
    audio = []
    num_samples = int(duration * sample_rate)

    scale = freq / sample_rate
    volume *= 127.5
    for x in range(num_samples):
        x *= scale
        audio.append(volume * (x - int(x)))  # The int function is equivalent to the floor function for positive numbers

    if reverse:
        audio.reverse()

    return create_sound_from_values(filename, audio, tag=tag, channels=1, sample_rate=sample_rate)


def create_square_wave(filename, duration, freq, tag=None, volume=1, sample_rate=7000):
    
    if not (isinstance(duration, float) or isinstance(duration, int)):
        raise GraphicsError(f"\n\nGraphicsError: duration value for square wave must be an int or float, not {duration}")
    if not (isinstance(volume, float) or isinstance(volume, int)):
        raise GraphicsError(f"\n\nGraphicsError: volume for square wave must be a float or int, not {volume}")
    if not (0 <= volume <= 1):
        raise GraphicsError(f"\n\nGraphicsError: volume for square wave must be between 0 & 1, not {volume}")

    if not (isinstance(sample_rate, float) or isinstance(sample_rate, int)):
        raise GraphicsError(f"\n\nGraphicsError: sample rate for square wave must be an integer or float,"
                            f" not {sample_rate}")
    
    audio = [0]
    num_samples = duration * sample_rate

    volume *= 127.5

    i = 0
    f = 0

    check = sample_rate / (freq * 0.5)
    for _ in range(num_samples):
        if f > check:
            i = 1 - i
            f = 0
            audio.append(volume * i)
        else:
            f += 1
            audio.append(audio[-1])
    audio.pop()

    return create_sound_from_values(filename, audio, tag=tag, channels=1, sample_rate=sample_rate)


def create_sound_from_values(filename, values, tag=None, channels=1, sample_rate=11050):
    
    if not (tag is None or isinstance(tag, str)):
        raise GraphicsError(f"\n\nGraphicsError: tag for sound must be a string or None, not {tag}")
    if not (isinstance(channels, int)):
        raise GraphicsError(f"\n\nGraphicsError: number of channels for audio must be an integer, not {channels}")
    if not (isinstance(sample_rate, float) or isinstance(sample_rate, int)):
        raise GraphicsError(f"\n\nGraphicsError: sample rate for audio must be an integer or float,"
                            f" not {sample_rate}")

    with waveopen(filename, "w") as wav_file:
        sampwidth = 1

        nframes = len(values)
        comptype = "NONE"

        wav_file.setparams((channels, sampwidth, sample_rate, nframes, comptype, "not compressed"))

        minimum = min(values)
        if minimum < 0:
            for i in range(len(values)):
                values[i] -= minimum

        for sample in values:
            wav_file.writeframes(structpack('B', int(sample)))

    return Sound(filename, tag=filename if tag is None else tag)
