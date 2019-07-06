#include "pch.h"

// Learn more about jsoncpp: https://github.com/open-source-parsers/jsoncpp
Json::Value AbstractScene::GetRootJson(LPCSTR jsonPath)
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
		const auto msg = reader.getFormattedErrorMessages();
		ThrowMyException("Parse json file failed:", msg.c_str());
	}

	return root;
}

void AbstractScene::SetPause(bool ispause)
{
	isPause = ispause;

	if (HasMusic()) // handle music for current main scene
	{
		if (isPause) Sounds::StopAt(GetBgMusic());
		else         Sounds::PlayLoop(GetBgMusic());
	}
}
