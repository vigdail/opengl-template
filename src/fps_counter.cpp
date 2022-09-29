#include "../include/vgl/fps_counter.h"
bool FpsCounter::tick(float delta_seconds, bool frame_rendered) {
  if (frame_rendered) {
    num_frames_++;
  }

  accumulated_time_ += delta_seconds;
  if (accumulated_time_ < avg_interval_secs_) {
    return false;
  }

  current_fps_ = static_cast<float>(num_frames_ / accumulated_time_);
  num_frames_ = 0;
  accumulated_time_ = 0.0;
  return true;
}
