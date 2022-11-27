#include "commlog.h"

void cmlg::LogMessage::flush() {
  if (GET_COMMON_LOGGER()->GetSeverity() > severity_) { return; }
  switch (severity_) {
    case cmlg::SEVERITY_TRACE: GET_COMMON_LOGGER()->Trace(loc_, message_text_); break;
    case cmlg::SEVERITY_DEBUG: GET_COMMON_LOGGER()->Debug(loc_, message_text_); break;
    case cmlg::SEVERITY_INFO: GET_COMMON_LOGGER()->Info(loc_, message_text_); break;
    case cmlg::SEVERITY_WARNING: GET_COMMON_LOGGER()->Warning(loc_, message_text_); break;
    case cmlg::SEVERITY_ERROR: GET_COMMON_LOGGER()->Error(loc_, message_text_); break;
    case cmlg::SEVERITY_FATAL: GET_COMMON_LOGGER()->Fatal(loc_, message_text_); break;
    case cmlg::SEVERITY_OFF: GET_COMMON_LOGGER()->Off(loc_, message_text_); break;
    default: break;
  }
}