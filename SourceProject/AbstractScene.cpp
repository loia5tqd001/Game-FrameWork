#include "pch.h"
#include "AbstractScene.h"

// Learn more about jsoncpp: https://github.com/open-source-parsers/jsoncpp
Json::Value AbstractScene::GetRootJson(LPCSTR jsonPath) const
{
	std::ifstream jsonFile(jsonPath);

	if (!jsonFile.is_open())
	{
		ThrowMyException("Can't open json file", jsonPath);
	}

	Json::Reader reader;
	Json::Value  root;

	if (!reader.parse(jsonFile, root))
	{
		LPCSTR msg = reader.getFormattedErrorMessages().c_str();
		ThrowMyException("Parse json file failed:", msg);
	}

	return root;
}
