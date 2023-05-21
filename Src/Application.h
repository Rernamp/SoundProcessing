#pragma once

#include <string>

#include "AudioFile.h"

#include <kfr/all.hpp>

namespace UDA {
	class Application {
		using AudioFileType = AudioFile<float>;
	public:
		Application(std::string pathToInputSignal, std::string pathToNoiseSignal, std::string pathToOutputFile) : _pathToOutputFile(pathToOutputFile) {
			AudioFileType _audioWav;

			auto fillBufferFromFile = [&](std::string pathToFile, AudioFileType::AudioBuffer& buffer) {
				_audioWav.load(pathToFile);
				buffer.resize(1);
				buffer[0] = _audioWav.samples[0];
			};

			fillBufferFromFile(pathToInputSignal, _inputSignal);
			fillBufferFromFile(pathToNoiseSignal, _noiseSignal);
		}

		void run() {
			AudioFileType::AudioBuffer _inputRecivedBuffer {_numberElements};

			generateRecivedSignal(_inputRecivedBuffer);

		}
	private:

		void generateRecivedSignal(AudioFileType::AudioBuffer& resultsBuffer) {
			using namespace kfr;

			univector<complex<float>> fftNoise = fft(_noiseSignal);
		}

		kfr::univector<kfr::complex<float>> fft(const AudioFileType::AudioBuffer& buffer) {
			using namespace kfr;
			univector<complex<float>> signal;

			for (const auto& element : buffer[0]) {
				signal.push_back(element);
			}

			return dft(signal);
		}

		kfr::univector<kfr::complex<float>> shiftSpectr(kfr::univector<kfr::complex<float>> inputSpect, float tauShift) {
			using namespace kfr;

			univector<complex<float>> result = inputSpect;
		}

		const std::size_t _numberElements = 4;
		const float soundSpeed = 330.0f;
		const float _distanceBetweenElement = 0.1f;
		const float _angleOfArrivalNoise = 60;

		AudioFileType::AudioBuffer _inputSignal{1};
		AudioFileType::AudioBuffer _noiseSignal{1};
		std::string _pathToOutputFile;
	};
}