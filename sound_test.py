from goopylib.sound.imports import *
from matplotlib import pyplot as plt

import wave

#create_square_wave("output.wav", 1, freq=440, volume=0.5)

sound_file = "output.wav"

with wave.open(sound_file) as wavfile:
    file = wavfile.readframes(wavfile.getnframes())
    channels = wavfile.getnchannels()

    file_data = [*file]
    file_channels = [file_data[channel::channels] for channel in range(channels)]

for channel in file_channels:
    plt.plot(channel)

sound = Sound(sound_file).play()

print("Length:", sound.get_length())
print("Samples/Sec:", sound.get_samples_per_second())
print("Channels:", sound.get_number_of_channels())

plt.show()
