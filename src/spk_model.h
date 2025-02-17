// Copyright 2020 Alpha Cephei Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef VOSK_SPK_MODEL_H
#define VOSK_SPK_MODEL_H

#include "base/kaldi-common.h"
#include "online2/online-feature-pipeline.h"
#include "nnet3/nnet-utils.h"
#include "ivector/plda.h"
#include "ivector/voice-activity-detection.h"
#include <atomic>

using namespace kaldi;
typedef unordered_map<std::string, Vector<BaseFloat>*, StringHasher> HashType;

class KaldiRecognizer;

class SpkModel {

public:
    SpkModel(const char *spk_path);
    void Ref();
    void Unref();

protected:
    friend class KaldiRecognizer;
    ~SpkModel() {};

    std::string plda_rxfilename;
    std::string train_ivector_rspecifier;
    std::string num_utts_rspecifier;

    kaldi::nnet3::Nnet speaker_nnet;
    kaldi::Vector<BaseFloat> mean;
    kaldi::Matrix<BaseFloat> transform;

    HashType train_ivectors;
    std::map<std::string, int32> num_utts;

    MfccOptions spkvector_mfcc_opts;
    VadEnergyOptions vad_opts;
    PldaConfig plda_config;

    Plda plda;

    std::atomic<int> ref_cnt_;
};

#endif /* VOSK_SPK_MODEL_H */
