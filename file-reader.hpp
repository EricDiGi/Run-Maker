#ifndef FILE_READER_HPP
#define FILE_READER_HPP

#include <string>
#include <fstream>
#include "road-graph.hpp"
#include "road.hpp"

class FileReader
{
	private:
		std::ifstream inFile;
	public:
		bool SetFile (std::string filename);
		~FileReader ();
		void IgnoreHeader ();
		void LoadData (RoadGraph &g);
		void close();
};

#endif /*FILE_READER_HPP*/
