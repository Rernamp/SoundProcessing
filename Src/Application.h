#pragma once

#include <string>
#include <cmath>
#include <array>

#include "AudioFile.h"

#include <Filters/FrostFilter.h>


namespace UDA {
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
				outputBuffer[0].push_back(_filter.do_sample(sample));
			}

			AudioFileType _outputAudioWav;
			_outputAudioWav.setAudioBuffer(outputBuffer);
			_outputAudioWav.setSampleRate(_fs);
			_outputAudioWav.save(_pathToOutputFile, AudioFileFormat::Wave);
		}
	private:

		static constexpr std::size_t _numberElements = 4;
		static constexpr std::size_t _filterOrder = 64;
		UDA::FrostAdaptiveFilter<_numberElements, _filterOrder> _filter {};

		AudioFileType::AudioBuffer _inputSignal{1};
		float _fs = 0.0f;
		std::string _pathToOutputFile;
	};
}