/*
Copyright (c) 2015, Sigurd Storve
All rights reserved.

Licensed under the BSD license.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the <organization> nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#pragma once
#include <string>
#include <vector>
#include <map>
#include "../LibBCSim.hpp"
#include "../BeamConvolver.hpp"

namespace bcsim {

enum class BeamProfileType {
    NOT_CONFIGURED = 0,
    ANALYTICAL,     // Analytical Gaussian beam profile
    LOOKUP          // Lookup-table based beam profile
};
    
// Common functionality for CPU- and GPU-algorithms.
class BaseAlgorithm : public IAlgorithm {
public:
    BaseAlgorithm();

    virtual ~BaseAlgorithm() { }
    
    // Handle common parameters for all algorithm implementations.
    virtual void set_parameter(const std::string& key, const std::string& value)    override;

    virtual std::string get_parameter(const std::string& key)                       const override;

    virtual std::vector<double> get_debug_data(const std::string& identifier)       const override;

    virtual void set_logger(ILog::ptr log_object) override;

protected:
    float       m_param_sound_speed;
    int         m_param_verbose;
    float       m_param_noise_amplitude;
    bool        m_param_use_arc_projection;
    int         m_radial_decimation;
    bool        m_enable_phase_delay;

    // The beam profile (analytical expression or LUT)
    BeamProfileType m_cur_beam_profile_type; 

    // storage of debug data
    std::map<std::string, std::vector<double>>  m_debug_data;
    
    ILog::ptr   m_log_object;   // class invariant: always valid (default dummy object)
};

}   // end namespace
