#pragma once

#include <cassert>
#include <cstdint>

class FpsCounter {
 public:
  explicit FpsCounter(float avg_interval_secs) : avg_interval_secs_{avg_interval_secs} {
    assert(avg_interval_secs > 0.0f);
  }

  bool tick(float delta_seconds, bool frame_rendered = true);

  inline float get_fps() const {
    return current_fps_;
  }

 private:
  const float avg_interval_secs_{0.5};
  uint32_t num_frames_{0};
  double accumulated_time_{0.0};
  float current_fps_{0.0f};
};
