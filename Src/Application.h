#pragma once

#include <string>
#include <cmath>

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
			std::size_t sizeOfFiles = std::min(_noiseSignal[0].size(), _inputSignal[0].size());
			auto delUnusedBuffer = [](std::vector<float>& buffer, std::size_t size) {
				if (buffer.size() != size) {
					buffer.erase(buffer.begin() + size, buffer.begin() + buffer.size());
				}
			};

			delUnusedBuffer(_inputSignal[0], sizeOfFiles);
			delUnusedBuffer(_noiseSignal[0], sizeOfFiles);
			
			_fs = _audioWav.getSampleRate();
		}

		void run() {
			kfr::univector<kfr::univector<kfr::complex<float>>> _inputRecivedBuffer {_numberElements};

			generateRecivedSignal(_inputRecivedBuffer);

		}
	private:

		void generateRecivedSignal(kfr::univector<kfr::univector<kfr::complex<float>>>& resultsBuffer) {
			using namespace kfr;

			univector<complex<float>> fftNoise = fft(_noiseSignal);

			float tauByOneElement = (_distanceBetweenElement*sind(_angleOfArrivalNoise))/(_soundSpeed);
			for (std::size_t i = 0; i < resultsBuffer.size(); i++) {
				resultsBuffer[i] = shiftSpectr(fftNoise, tauByOneElement * i, _fs);
			}
			
		}

		kfr::univector<kfr::complex<float>> fft(const AudioFileType::AudioBuffer& buffer) {
			using namespace kfr;
			univector<complex<float>> signal;

			for (const auto& element : buffer[0]) {
				signal.push_back(element);
			}

			return dft(signal);
		}

		kfr::univector<kfr::complex<float>> shiftSpectr(kfr::univector<kfr::complex<float>> inputSpectr, float tauShift, float fs) {
			using namespace kfr;
			univector<complex<float>> result {};
			inputSpectr[0] = 0;

			auto nOne = 1;
			auto numberElementOfOneZone = std::roundl(inputSpectr.size() / 2) - 1;

			for (std::size_t i = 0; i <= numberElementOfOneZone; i++) {
				auto fTau = ((2 + 2 + nOne - 1)/2) + i*nOne;

				kfr::complex<float> shiftValue = 0.0f;
				for (std::size_t j = 2 * i * nOne; j < (1 + nOne + i * nOne); j++) {
					shiftValue = inputSpectr[j] * kfr::cexp(- complex<float>(0, -1) * 2 * kfr::constants<float>::pi * fTau * tauShift * fs / inputSpectr.size());
					result.push_back(shiftValue);
				}
			}

			univector<complex<float>> rightPart{};

			std::size_t sizeBuffer = result.size();
			if (inputSpectr.size() % 2 == 0) {
				result.back() = result.back().real();
				
				for (std::size_t i = sizeBuffer - 1; i > 0; i--) {
					rightPart.push_back(cconj(result[i]));
				}
			}
			else {
				for (std::size_t i = sizeBuffer; i > 0; i--) {
					rightPart.push_back(cconj(result[i]));
				}
			}

			result.insert(result.begin(), inputSpectr[0]);
			result.insert(result.end(), rightPart.begin(), rightPart.end());


			return result;
		}

		const std::size_t _numberElements = 4;
		const float _soundSpeed = 330.0f;
		const float _distanceBetweenElement = 0.1f;
		const float _angleOfArrivalNoise = 60;

		AudioFileType::AudioBuffer _inputSignal{1};
		AudioFileType::AudioBuffer _noiseSignal{1};
		float _fs = 0.0f;
		std::string _pathToOutputFile;
	};
}