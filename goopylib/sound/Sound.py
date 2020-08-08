from ctypes import c_buffer, windll
from time import sleep
from sys import getfilesystemencoding

from goopylib.util import GraphicsError

# Right now, the Sound module is only compatible with windows & wav files

# Support needed for wav, mp3, m4a, flac, wma, aac, MIDI, MusicXML

"""
ctypes is a library that implements C data types and allows you to use DLLs 

https://support.microsoft.com/en-in/help/815065/what-is-a-dll
DLLs (Digital Link Library) are libraries written (by?) for Microsoft that can control general elements of windows 
    .cpl are Control Panel DLLs and can control Control Panel Setings
    .ocx are ActiveXControls. For example, the Condlg32 DLL allows you to create dialog boxes 
    .drv are Device Drivers. For example, they can control printing to a printer. 

MCIs are basically multimedia devices and they can be controlled using certain commands.

Open Device -> Send Commands -> Close Device 

MCI Commands:

    open: https://docs.microsoft.com/en-us/windows/win32/multimedia/open
    close: https://docs.microsoft.com/en-us/windows/win32/multimedia/close

    ----------------------------------------------------------------------------------------------------
    set: https://docs.microsoft.com/en-us/windows/win32/multimedia/set	
    SET FLAGS FOR WAVEAUDIO:

        "set {alias} {flags}"

        alignment {integer} - Sets the alignment of data blocks relative to the start of data passed to the 
                              waveform-audio device.

                              "Data alignment refers to where data is located in memory. All data is at least 
                              1-byte aligned, meaning that it starts at any one byte in memory. Data that is 
                              n-byte aligned is located somewhere with a memory address that is an exact multiple 
                              of n bytes." 
                                    - https://www.gamasutra.com/view/feature/3942/data_alignment_part_1.php?print=1

                              Notes from: https://www.youtube.com/watch?v=OKjOZBaKlOc
                                  - Data has to be aligned according to its length
                                  - Data that is 1 byte in sized can be saved anywhere in memory

                                  - addresses of 2 bytes of data (halfwords) must be multiples of 2 (even numbers)
                                        0, 2, 4, etc. - and not 1, 3, 5, etc.

                                  - addresses of 4 bytes of data (words) must be multiples of 4
                                  - addresses of 8 bytes of data (doublewords) must be multiples of 8


                                  Here is an example of aligning 4 bytes of data
                                  -----------
                                  0000 - it can start here
                                  0001 
                                  0002                      # The distance between each starting position is 4 addresses
                                  0003
                                  0004 - it can start here
                                  0005
                                  0006                      # Each one of these addresses is a byte
                                  0007
                                  0008 - it can start here
                                  0009
                                  000a 
                                  000b
                                  000c - it can start here
                                  000d
                                  000e
                                  000f
                                  0010 - it can start here
                                  0011 
                                  0012 
                                  0013 
                                  0014 - it can start here
                                  0015 
                                  0016 
                                  0017 
                                  0018 - it can start here
                                  0019 
                                  001a 
                                  001b 
                                  001c - it can start here
                                  001d 
                                  001e 
                                  001f            

        audio left off - These next ones control whether the audio is outputted in the left & right channels
        audio left on    The channels (based on my limted knowledge) only matter if you are using head/ear phones
        audio right off  These are not valid for MCIWAVE, MCISEQ, and Video Overlay deviced. No idea what this means,
        audio right on   but it doesn't work on my computer using the default speaker or headphones

        time format bytes - The time format of the audio, ie how do reference a point in time of the audio
        time format ms - the length of the audio in these units depends on the time format. 
        time format samples

    ----------------------------------------------------------------------------------------------------
    play: https://docs.microsoft.com/en-us/windows/win32/multimedia/play
    PLAY FLAGS FOR AUDIO:

        "play {alias} {flags & values}"

        from {position}
"""

"""
WAV File Format (http://soundfile.sapp.org/doc/WaveFormat/):

RIFF Chunk
    0 - ChunkID (4 bytes) - the letters 'RIFF'

    4 - ChunkSize (4 bytes) - "24 08 00 00" with the most significant byte being on the right. 
                              So converting 00 00 08 24 from hexadecimal to decimal gives 2084, which is the 
                              size of the rest of the RIFF following this byte. The total size of the chunk is then
                              8 bytes + this number which counts the ChunkID's & ChunkSize's 4 bytes each (8 bytes)

    8 - Format (4 bytes) - the letters 'WAVE'

fmt SubChunk

    12 - SubchunkID (4 bytes) - The letters 'fmt ' (note the space)

    Most significant byte on the right for the rest of the values in this subchunk

    16 - SubchunkSize (4 bytes) - 16 for PCM (Pulse-Code modulation)
    20 - AudioFormat (2 bytes) - 1 for PCM, otherwise there is some sort of compression

    22 - NumChannels (2 bytes) - Gives the number of channels in the audio. Mono is 1, Sterio is 2, etc.
    24 - SampleRate (4 bytes) - Number of samples per second
    28 - ByteRate (4 bytes) - SampleRate * NumChannels * BitsPerSample/8, the number of bytes to read per second

    32 - BlockAlign (2 bytes) - NumChannels * BitsPerSample/8, number of bytes for 1 sample including all channels

    34 - BitsPerSample (2 bytes)

data SubChunk

    36 - SubchunkID (4 bytes) - The letters 'data'

    Most significant byte on the right for the rest of the values in this subchunk

    40 - SubchunkSize (4 bytes) - The size of the data in the rest of this subchunk
    44 - Data (* bytes) - The actual sound data

Example WAV Audio File - eatghost.wav
----------------------------------------------------------------
RIFF Chunk

    RIFF\x04\x19\x00\x00WAVE

    0 ChunkID - RIFF
    4 ChunkSize - \x04\x19\x00\x00 = 00 00 19 04 (hex) = 6404 bytes
    8 Format - WAVE

fmt Subchunk

    I've added | between each field to help organize them. These are not part of the file.

    fmt \x10\x00\x00\x00|\x01\x00|\x01\x00|\x11\x2b\x00\x00|\x11\x2b\x00\x00|\x01\x00|\x08\x00

    12 SubchunkID - fmt 
    16 SubchunkSize - \x10\x00\x00\x00 = 00 00 00 10 (hex) = 16 bytes
    20 AudioFormat - \x01\x00 = 00 01 (hex) = 1 which stands for PCM
    22 NumChannels - \x01\x00 = 00 01 (hex) = 1 which means the audio is Mono
    24 SampleRate - \x11\x2b\x00\x00 = 00 00 2b 11 (hex) = 11025 Hz
    28 ByteRate - \x11\x2b\x00\x00 = 00 00 2b 11 (hex) = 11025 bytes/sec 
                                     which equals SampleRate * NumChannels * BitsPerSample/8
    32 Block Align - \x01\x00 = 00 01 (hex) = 1 byte/sample 
                                which equals NumChannels * BitsPerSample/8
    34 BitsPerSample - \x08\x00 = 00 08 (hex) = 8 bits/sample

data Subchunk   

    data\xb4\x18\x00\x00 

    36 SubchunkID - data
    40 SubchunkSize - \xb4\x18\x00\x00 = 00 00 18 b4 (hex) = 6324 bytes

    44 Data - The rest of the 6324 bytes are the data of the sound
"""

# The code for this function has pretty much (few changes) been copied from the playsound module
# https://github.com/TaylorSMarks/playsound
# Without the playsound module, I would have never known how to get started with playing sounds and it sort of paved
# the way for this part of goopylib.
def windows_command(command):
    buf = c_buffer(255)
    command = command.encode(getfilesystemencoding())

    error_code = windll.winmm.mciSendStringA(command, buf, 254, 0)

    if error_code:
        error_buffer = c_buffer(255)
        windll.winmm.mciGetErrorStringA(error_code, error_buffer, 254)
        raise GraphicsError(
            f'\n\tError {error_code} for command: \n\t\t{command.decode()}\n\t{error_buffer.value.decode()}')
    return buf.value


# SOME NOTES FOR GOOPY
# * The Alias names can be set by the user to reference certain sounds using a tag
# * There must be functions to get the different flags of the audio like number of channels & stuff
# * The user must be able to specify the time format type (for advanced purposes), default remains ms

# IMPORTANT: For Windows 2000/XP, send the stop command before closing

class Sound:
    file_instances = {*()}
    instances = {*()}

    def __init__(self, filepath, tag=None):
        tag = filepath if tag is None else tag
        i = 0
        self.tag = tag
        while self.tag in Sound.file_instances:
            self.tag = f"{tag}{i}"
            i += 1

        self.filepath = filepath

        windows_command(f'open "{self.filepath}" alias {self.tag}')
        windows_command(f'set {self.tag} time format samples')

        self.raw_duration = int(windows_command(f'status {self.tag} length').decode())

        self.is_playing = False
        self.is_paused = False

        self.start_crop = 0
        self.end_crop = 0

        Sound.file_instances.add(self.tag)
        Sound.instances.add(self)

    def __check_playing(self):
        if int(windows_command(f"status {self.tag} position").decode()) == \
                int(windows_command(f"status {self.tag} length").decode()):
            self.is_playing = False

    def play(self, wait_for_finish=False, start=0, end=0):
        windows_command(f"play {self.tag} from {start} to {self.raw_duration - end} notify")

        self.is_playing = True
        self.is_paused = False

        if wait_for_finish:
            sleep(self.raw_duration / 1000)

        return self

    def stop(self):
        windows_command(f"stop {self.tag}")

        self.is_playing = False
        self.is_paused = False

        return self

    def pause(self):
        self.__check_playing()
        if self.is_playing:
            windows_command(f"pause {self.tag}")
            self.is_paused = True
        return self

    def unpause(self):
        self.__check_playing()
        if self.is_playing:
            windows_command(f"resume {self.tag}")
            self.is_paused = False
        return self

    def crop(self, start=0, end=0):
        windows_command(f"delete {self.tag} from {self.raw_duration - end}")  # Cropping the sound
        windows_command(f"delete {self.tag} from 0 to {start}")

        self.raw_duration = int(windows_command(f'status {self.tag} length').decode())

        self.start_crop = start
        self.end_crop = end

        return self

    def save(self, filename):
        windows_command(f"save {self.tag} {filename}")
        return self

    def destroy(self):
        if self.tag in Sound.file_instances:
            windows_command(f"stop {self.tag}")
            windows_command(f"close {self.tag}")
            Sound.file_instances.remove(self.tag)

            self.is_playing = False
        return self

    # ------------------------------
    # GETTER FUNCTIONS

    def get_filepath(self):
        return self.tag

    def get_length(self):
        return int(windows_command(f"status {self.tag} length").decode())

    def get_bits_per_sample(self):
        return int(windows_command(f"status {self.tag} bitspersample").decode())

    def get_bytes_per_second(self):
        return int(windows_command(f"status {self.tag} bytespersec").decode())

    def get_number_of_channels(self):
        return int(windows_command(f"status {self.tag} channels").decode())

    def get_samples_per_second(self):
        return int(windows_command(f"status {self.tag} samplespersec").decode())

    def get_start_crop(self):
        return self.start_crop

    def get_end_crop(self):
        return self.end_crop

    def get_current_position(self):
        return int(windows_command(f"status {self.tag} position").decode())

    def get_percent_complete(self):
        return int(windows_command(f"status {self.tag} position").decode()) \
               / int(windows_command(f"status {self.tag} length").decode())

    def check_is_playing(self):
        if int(windows_command(f"status {self.tag} position").decode()) == \
                int(windows_command(f"status {self.tag} length").decode()):
            self.is_playing = False
        return self.is_playing and not self.is_paused
