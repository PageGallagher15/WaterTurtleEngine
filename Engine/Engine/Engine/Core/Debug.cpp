#include "Debug.h"

MessageType Debug::currentSeverity = MessageType::TYPE_NONE;

void Debug::DebugInit() {
	std::ofstream out;
	out.open("Debug_Log.txt", std::ios::out);
	out.close();
	currentSeverity = MessageType::TYPE_INFO;
}

void Debug::SetSeverity(MessageType type_) {
	currentSeverity = type_;
}


void Debug::Log(const MessageType type_, const std::string& message_, const std::string filename_, const int line_) {
	if (type_ <= currentSeverity && currentSeverity > MessageType::TYPE_NONE) {
		std::ofstream file;
		file.open("Debug_Log.txt", std::ios::out | std::ios::app);
		file << message_ << " in " << filename_ << " on line: " << line_;
		file.flush();
		file.close();
	}
}

void Debug::Info(const std::string& message_, const std::string filename_, const int line_) {
	Log(MessageType::TYPE_INFO, "[INFO]" , filename_, line_);
}

void Debug::Trace(const std::string& message_, const std::string filename_, const int line_) {
	Log(MessageType::TYPE_TRACE, "[TRACE]" , filename_, line_);
	
}

void Debug::Warning(const std::string& message_, const std::string filename_, const int line_) {
	Log(MessageType::TYPE_WARNING, "[WARNING]", filename_, line_);

}

void Debug::Error(const std::string& message_, const std::string filename_, const int line_) {
	Log(MessageType::TYPE_ERROR, "[ERROR]", filename_, line_);
	
}

void Debug::FatalError(const std::string& message_, const std::string filename_, const int line_) {
	Log(MessageType::TYPE_FATAL_ERROR, "[FATALERROR]", filename_, line_);
	
}