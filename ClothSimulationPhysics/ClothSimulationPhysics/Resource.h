#pragma once
#include <string>
#include <glm/glm.hpp>
#include <vector>

namespace Utility
{
	const unsigned int SCR_WIDTH = 1600;
	const unsigned int SCR_HEIGHT = 800;
	const glm::vec3 Gravity = { 0.0f, -9.8f, 0.0f };
};

namespace Shaders
{
	const std::string SingleColorShaderFrag = "Resources/Shaders/SingleColorShader.fs";
	const std::string FogShaderVert = "Resources/Shaders/FogObjectShader.vs";
	const std::string FogShaderFrag = "Resources/Shaders/FogObjectShader.fs";
	const std::string ModelFogShaderVert = "Resources/Shaders/FogModel.vs";
	const std::string ModelFogShaderFrag = "Resources/Shaders/FogModel.fs";
	const std::string ObjectShaderVert = "Resources/Shaders/ObjectShaderV.vs";
	const std::string ObjectShaderFrag = "Resources/Shaders/ObjectShaderF.fs";
	const std::string ModelShaderVert = "Resources/Shaders/Model.vs";
	const std::string ModelShaderFrag = "Resources/Shaders/Model.fs";
	const std::string CubeMapShaderFrag = "Resources/Shaders/CubeShader.fs";
	const std::string CubeMapShaderVert = "Resources/Shaders/CubeShader.vs";
	const std::string FogCubeMapShaderVert = "Resources/Shaders/FogCubeShader.vs";
	const std::string FogCubeMapShaderFrag = "Resources/Shaders/FogCubeShader.fs";
	const std::string TessShaderVert = "Resources/Shaders/TessShader.vs";
	const std::string TessShaderTCSQuad = "Resources/Shaders/TessShaderQuad.tcs";
	const std::string TessShaderTESQuad = "Resources/Shaders/TessShaderQuad.tes";
	const std::string TessShaderTCSTri = "Resources/Shaders/TessShaderTri.tcs";
	const std::string TessShaderTESTri = "Resources/Shaders/TessShaderTri.tes";
	const std::string TessShaderFrag = "Resources/Shaders/TessShader.fs";
	const std::string GeometryShaderVert = "Resources/Shaders/GeometryShader.vs";
	const std::string GeometryShaderRedVert = "Resources/Shaders/GeometryShaderRed.vs";
	const std::string GeometryShaderGeom = "Resources/Shaders/GeometryShader.gs";
	const std::string GrassShaderGeom = "Resources/Shaders/GrassGeometryShader.gs";
	const std::string GrassShaderFrag = "Resources/Shaders/GrassShader.fs";
	const std::string GrassQuadShaderGeom = "Resources/Shaders/GrassGeometryShaderQuads.gs";
	const std::string GrassQuadShaderFrag = "Resources/Shaders/GrassShaderQuads.fs";
	const std::string TextShaderVert = "Resources/Shaders/Text.vs";
	const std::string TextShaderFrag = "Resources/Shaders/Text.fs";
	const std::string FrameBufferVert = "Resources/Shaders/FrameBuffer.vs";
	const std::string FrameBufferFrag = "Resources/Shaders/FrameBuffer.fs";
}

namespace HeightMaps
{
	const std::string MountainTerrain = "Resources/HeightMaps/coastMountain513.raw";
	const std::string LargePlateauTerrain = "Resources/HeightMaps/Heightmap_Plateau.raw";
}

namespace TexturePaths
{
	const std::string CubeMapTexture = "Resources/Textures/CubeMap/";
	const std::string WaterTexture = "Resources/Textures/Water.png";
	const std::string WaterTransparentTexture = "Resources/Textures/WaterTransparent.png";
	const std::string BlueSquareTexture = "Resources/Textures/Bluesquare.png";
	const std::string TestTexture = "Resources/Textures/desert.jpg";
	const std::string UpTexture = "Resources/Textures/Up.png";
	const std::string DownTexture = "Resources/Textures/Down.png";
	const std::string GrassTexture = "Resources/Textures/grassTex.png";
	const std::string WireFrameTexture = "Resources/Textures/Wireframe.png";
}

namespace SoundnFonts
{
	const std::string NormalFontString = "Resources/Fonts/arial.ttf";
	const std::string GameOver = "Resources/Audio/Game_over_music.wav";
	const std::string BackgroundMusic = "Resources/Audio/CrabRave.wav";
	const std::string MenuMusic = "Resources/Audio/Menu_music.wav";
}