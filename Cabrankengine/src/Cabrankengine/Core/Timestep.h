#pragma once

namespace cabrankengine {

	// Timestep is a class that represents the time elapsed between two frames.
	class Timestep {
		public:
			Timestep(float time = 0.0f) : m_Time(time) {}

			// Returns the time in seconds.
			float getSeconds() const { return m_Time; }
		
			// Returns the time in milliseconds.
			float getMilliseconds() const { return m_Time * 1000.0f; }
		
			// Conversion operator to float, allowing Timestep to be used in places where a float is expected.
			operator float() const { return m_Time; }
	
		private:
			float m_Time; // Actual timestep in seconds
	};
}
