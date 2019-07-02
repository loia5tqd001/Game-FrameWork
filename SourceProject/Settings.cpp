#include "pch.h"

void TextBlock::Draw(D3DCOLOR strColor, D3DCOLOR keyCodeColor) const
{
	KeyCodeFonts::DrawString(strDraw, posDraw, strColor);
	if (keyCode != NULL)
	{
		const Vector2 posDrawKeyCode = posDraw + Vector2{ 160.0f, 0.0f };
		KeyCodeFonts::DrawKeyCode(keyCode, posDrawKeyCode, keyCodeColor);
	}
}

Settings::Settings()
{
	// Init string draw for textblocks
	textblocks[TextBlocks::Left   ].strDraw = "LEFT";
	textblocks[TextBlocks::Right  ].strDraw = "RIGHT";
	textblocks[TextBlocks::Jump   ].strDraw = "JUMP";
	textblocks[TextBlocks::Default].strDraw = "DEFAULT";
	textblocks[TextBlocks::Back   ].strDraw = "BACK";

	// Init position draw for textblocks
	for (int i = TextBlocks::Left; i < TextBlocks::Count; i++) {

		if (i < TextBlocks::CountKCtrl) textblocks[i].posDraw.x = 70.0f;
		else /*Default, Back*/          textblocks[i].posDraw.x = 120.0f;

		textblocks[i].posDraw.y = 50.0f + i * 30.0f;
	}

	// Init keyCode for textblocks
	ResetDefaultKeyControl();
}

void Settings::ResetDefaultKeyControl()
{
	textblocks[TextBlocks::Left ].keyCode = VK_LEFT;
	textblocks[TextBlocks::Right].keyCode = VK_RIGHT;
	textblocks[TextBlocks::Jump ].keyCode = VK_SPACE;		
}

BYTE Settings::Get(KeyControls kControl) const
{
	assert(kControl >= KeyControls::Left && kControl < KeyControls::CountKCtrl);
	return textblocks[kControl].keyCode;
}

void Settings::SetOpening(bool isOpening)
{
	isSceneOpening = isOpening;
	isEditing = false;
}

bool Settings::IsValidKeyControl(BYTE keyCode)
{
	if (keyCode >= VK_NUMPAD0 && keyCode <= VK_NUMPAD9)     return true;
	if (keyCode >= '0' && keyCode <= '9')                   return true;
	if (keyCode >= 'A' && keyCode <= 'Z' && keyCode != 'M') return true;
	if (keyCode >= VK_LEFT && keyCode <= VK_DOWN)           return true;
	if (keyCode == VK_SPACE)                                return true;
	return false;
}

void Settings::Draw() const
{
	if (!isSceneOpening) return;

	// semi-transparent-black background
	Game::Instance().DrawSolidRect( { 0.0f, 0.0f, 320.0f, 240.0f }, Colors::DarkTransparentBlack);
	
	// title 'Settings'
	KeyCodeFonts::DrawString("Settings", { 126.0f, 10.0f }, Colors::White);

	// Draw frame background
	//Game::Instance().DrawSolidRect( { 30.0f, 30.0f, 290.0f, 210.0f }, Colors::Black); // center solid
	Game::Instance().DrawOutLine( {  27.0f,  27.0f, 293.0f, 213.0f }, 3, Colors::DimBlue); // center
	Game::Instance().DrawOutLine( {  20.0f,  20.0f,  30.0f,  30.0f }, 3, Colors::DimBlue); // topleft
	Game::Instance().DrawOutLine( { 290.0f,  20.0f, 300.0f,  30.0f }, 3, Colors::DimBlue); // topright
	Game::Instance().DrawOutLine( {  20.0f, 210.0f,  30.0f, 220.0f }, 3, Colors::DimBlue); // bottomleft
	Game::Instance().DrawOutLine( { 290.0f, 210.0f, 300.0f, 220.0f }, 3, Colors::DimBlue); // bottomright

	// Draw textblocks
	for (int i = TextBlocks::Left; i < TextBlocks::Count; i++)
	{
		if (i != curCursor) { // normal textblock
			textblocks[i].Draw(Colors::White, Colors::White);
		} 
		else if (isEditing) { // selected textblock editing
			textblocks[i].Draw(Colors::DimRed , Colors::DimRed);
		} 
		else { // selected textblock but not editing
			textblocks[i].Draw(Colors::DimBlue, Colors::DimBlue);
		}
	}
}

void Settings::OnKeyDown(BYTE keyCode)
{
	if (isEditing) // selected textblock is in editing
	switch (curCursor) {
		case TextBlocks::Left:
		case TextBlocks::Right:
		case TextBlocks::Jump:
			if (keyCode == VK_RETURN) {
				isEditing = false;
				Sounds::PlayAt(SoundId::Cursor);
			} 
			else if (IsValidKeyControl(keyCode)){
				TextBlock& curTextBlock = textblocks[curCursor];

				for (int i = 0; i < KeyControls::CountKCtrl; i++) { // change keyControl if an exist textblock has same key
					if (textblocks[i].keyCode == keyCode) {
						textblocks[i].keyCode = curTextBlock.keyCode;
						break;
					}
				}
				curTextBlock.keyCode = keyCode;
				Sounds::PlayAt(SoundId::Cursor);
			}
			break;

		default:
			ThrowMyException("curCursor has an invalid value!!");
	}

	else // isn't editing any textblock
	switch (keyCode) {
		case VK_UP: 
			if (curCursor == TextBlocks::Left) curCursor = TextBlocks::Back;
			else                               curCursor = TextBlocks( curCursor - 1 );
			Sounds::PlayAt(SoundId::Cursor);
			break;		

		case VK_DOWN: 
			if (curCursor == TextBlocks::Back) curCursor = TextBlocks::Left;
			else                               curCursor = TextBlocks( curCursor + 1 );
			Sounds::PlayAt(SoundId::Cursor);
			break;

		case VK_RETURN: 
			if      (curCursor == TextBlocks::Back   )  SceneManager::Instance().ToggleSettingScene();
			else if (curCursor == TextBlocks::Default)  ResetDefaultKeyControl(), Sounds::PlayAt(SoundId::Cursor);
			else                                        isEditing = true        , Sounds::PlayAt(SoundId::Cursor);
			break;
	}
}

Settings& Settings::Instance()
{
	static Settings instance;
	return instance;
}
