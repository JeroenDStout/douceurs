#pragma once

namespace douceurs::sugar {

	struct once
	{
		bool is_first = true;

		void reset()
		{
			is_first = true;
		}

		bool get_once()
		{
			if (!is_first)
				return false;

			is_first = false;
			return true;
		}

		bool operator()() { return get_once(); }
	};

}