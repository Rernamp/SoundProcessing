#pragma once

#include <string>
#include <cmath>
#include <array>

#include "AudioFile.h"

#include "Filters/LC_NLMS_Implement.h"



namespace UDA {

	class Transmitter : public ITransmitter {
	public:
		using TypeData = float;
		Transmitter(AudioFile<float>::AudioBuffer& buffer) : _buffer(buffer) {
		}
		std::size_t append(uint8_t* data, std::size_t size) override {
			for (std::size_t i = 0; i < size / sizeof(TypeData); i++) {
				float value = *reinterpret_cast<TypeData*>(data);
				_buffer[0].push_back(value);
				data += sizeof(TypeData);
			}
		}
	private:
		AudioFile<float>::AudioBuffer& _buffer;
	};	

	class Application {
		using AudioFileType = AudioFile<float>;
	public:
		Application(std::string pathToInputSignal, std::string pathToOutputFile) : _pathToOutputFile(pathToOutputFile) {
			AudioFileType _inputAudioWav;
			_inputAudioWav.load(pathToInputSignal);
			_inputSignal = _inputAudioWav.samples;
			_fs = _inputAudioWav.getSampleRate();
		}

		void run() {
			AudioFileType::AudioBuffer outputBuffer {1};

			std::array<float, _numberElements> sample {};
			for (std::size_t i = 0; i < _inputSignal[0].size(); i++) {
				for (std::size_t j = 0; j < _numberElements; j++) {
					sample[j] = _inputSignal[j][i];
				}				
				outputBuffer[0].push_back(10.0f);
			}

			AudioFileType _outputAudioWav;
			_outputAudioWav.setAudioBuffer(outputBuffer);
			_outputAudioWav.setSampleRate(_fs);
			_outputAudioWav.save(_pathToOutputFile, AudioFileFormat::Wave);
		}
	private:

		static constexpr std::size_t _numberElements = 4;
		static constexpr std::size_t _filterOrder = 64;

		AudioFileType::AudioBuffer _inputSignal{1};
		float _fs = 0.0f;
		std::string _pathToOutputFile;
	};
}