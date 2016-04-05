import sys
import wave
import struct
import numpy as np
import matplotlib.pyplot as plt

from scipy.signal import butter, lfilter, freqz

# usage:  python audioEqualizer.py <wave_file_name.wav> <lowpass|highpass>

bufferWidth = 4096

def fftFreqScale(dataArray, fs, scalingTuples):
    '''
    scalingTuples are all (frequency, factor)
    interpreted:  up to {frequency}, scale by {factor}
    '''

    fft = np.fft.fft(dataArray)

    freqArray = fs * np.fft.fftfreq(len(dataArray))

    halfScalingArray = np.zeros([len(dataArray) / 2], dtype=np.float)

    currentScalingIndex = 0

    for i in range(len(dataArray) / 2):
        if freqArray[i] > scalingTuples[currentScalingIndex][0]:
            currentScalingIndex+= 1

        halfScalingArray[i] = scalingTuples[currentScalingIndex][1]

    dummy = np.concatenate((halfScalingArray, np.array([halfScalingArray[-1]])))
    scalingArray = np.concatenate((dummy , halfScalingArray[:0:-1]))


    fft = fft * scalingArray

    return np.round(np.real(np.fft.ifft(fft)))

ORDER = 10

def bandpassFreqScale(dataArray, fs, scalingTuples, filterArray):
    output = np.zeros([len(dataArray)], dtype=np.int16)

    b, a = filterArray[0]
    filteredSignal = lfilter(b, a, dataArray)
    output = output + filteredSignal.astype(np.int16)

    b, a = filterArray[1]
    filteredSignal = lfilter(b, a, dataArray)
    output = output + filteredSignal.astype(np.int16)

    '''
    plt.subplot(211)
    plt.plot(dataArray)
    plt.subplot(212)
    plt.plot(output)
    plt.show()
    '''

    return output

f = wave.open(sys.argv[1], 'r');
w = wave.open(sys.argv[1].split(".")[0] + "Output.wav", 'w');

w.setnchannels(f.getnchannels())
w.setsampwidth(f.getsampwidth())
w.setframerate(f.getframerate())
w.setcomptype(f.getcomptype(), f.getcompname())

preFilter = np.array([])
postFilter = np.array([])

oneChannelInput = np.zeros([bufferWidth], dtype=np.int16)
otherChannelInput = np.zeros([bufferWidth], dtype=np.int16)

oneChannelOutput = np.zeros([bufferWidth], dtype=np.int16)
otherChannelOutput = np.zeros([bufferWidth], dtype=np.int16)

if sys.argv[2] == 'highpass':
    attenTuples = [(400.0, .10), (1e6, 1.0)]
elif sys.argv[2] == 'lowpass':
    attenTuples = [(400.0, 1.0), (1e6, .10)]
else:
    attenTuples = [(1e6, 1.0)]

fs = 44.1e3
filterArray = []
b, a = butter(ORDER, 400.0 / (fs * 0.5), btype='low')

'''
w, h = freqz(b, a, worN=2000)
plt.plot((fs * 0.5 / np.pi) * w, abs(h), label="order = %d" % ORDER)
plt.show()
'''

filterArray.append((b,a))
b, a = butter(ORDER, 400.0 / (fs * 0.5), btype='high')

'''
w, h = freqz(b, a, worN=2000)
plt.plot((fs * 0.5 / np.pi) * w, abs(h), label="order = %d" % ORDER)
plt.show()
'''

filterArray.append((b,a))

# Samples from previous frame to be present at beginning of next frame
oneChannelOverlapInput = np.zeros([bufferWidth / 4])
#oneChannelOverlapOutput = np.zeros([bufferWidth / 2])
otherChannelOverlapInput = np.zeros([bufferWidth / 4])
#otherChannelOverlapOutput = np.zeros([bufferWidth / 2])

while (f.tell() < f.getnframes()):
    print f.tell()
    oneChannelInput[0:bufferWidth/4] = oneChannelOverlapInput
    otherChannelInput[0:bufferWidth/4] = otherChannelOverlapInput

    for i in range(bufferWidth/4, bufferWidth):
        frame = f.readframes(1)
        oneChannelInput[i] = struct.unpack('<h', frame[0:2])[0]
        otherChannelInput[i] = struct.unpack('<h', frame[2:4])[0]

    # Theoretically, do processing stuff here
    oneChannelOutput = bandpassFreqScale(oneChannelInput, f.getframerate(), attenTuples, filterArray)
    otherChannelOutput = bandpassFreqScale(otherChannelInput, f.getframerate(), attenTuples, filterArray)

    packedData = ''

    #oneChannelFiltered = oneChannelOutput[0:bufferWidth/2] + oneChannelOverlapOutput
    #otherChannelFiltered = otherChannelOutput[0:bufferWidth/2] + otherChannelOverlapOutput


    # Drop all overlap samples when writing out data
    for i in range(bufferWidth / 4, bufferWidth * 3 / 4):

        packedData += struct.pack('<h', oneChannelOutput[i])
        packedData += struct.pack('<h', otherChannelOutput[i])

    plt.subplot(211)
    plt.plot(oneChannelInput[bufferWidth/4:bufferWidth*3/4])
    plt.subplot(212)
    plt.plot(oneChannelOutput[bufferWidth/4:bufferWidth*3/4])
    plt.show()

    w.writeframesraw(packedData)

    #preFilter = np.concatenate((preFilter, oneChannelInput[bufferWidth/4:bufferWidth*3/4]))
    #postFilter = np.concatenate((postFilter, oneChannelOutput[bufferWidth/4:bufferWidth*3/4]))

    oneChannelOverlapInput = oneChannelInput[bufferWidth*3/4:bufferWidth]
    #oneChannelOverlapOutput = oneChannelOutput[bufferWidth*3/4:bufferWidth]
    otherChannelOverlapInput = otherChannelInput[bufferWidth*3/4:bufferWidth]
    #otherChannelOverlapOutput = otherChannelOutput[bufferWidth/2:bufferWidth]

'''
plt.subplot(211)
plt.plot(preFilter[350000:400000])
plt.subplot(212)
plt.plot(postFilter[350000:400000])
plt.show()
'''

w.close()
