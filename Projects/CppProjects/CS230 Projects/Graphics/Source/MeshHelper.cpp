//------------------------------------------------------------------------------
//
// File Name:	MeshHelper.cpp
// Author(s):	Gryphon McLaughlin (gryphon.mclaughlin)
// Project:	CS230 6.1.6 ASSIGNMENT - Graphics
// Course:	WANIC VGP2
//
// Copyright © 2019 DigiPen (USA) Corporation.
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Include Files and Using Declarations:
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "MeshHelper.h"

using namespace Beta;

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

// Create a colored mesh consisting of a single triangle using the Beta Framework.
// Params:
//   color0 = The color of vertex 0.
//   color1 = The color of vertex 1.
//   color2 = The color of vertex 2.
// Returns:
//	 A pointer to the newly created mesh.
Mesh* CreateTriangleMesh(const Color& color0, const Color& color1,
	const Color& color2)
{
	Vertex rightPoint = Vertex(Vector2D(0.5f, 0.0f), color0);
	Vertex leftTopPoint = Vertex(Vector2D(-0.5f, 0.5f), color1);
	Vertex leftBottomPoint = Vertex(Vector2D(-0.5f, -0.5f), color2);

	EngineGetModule(MeshFactory)->AddTriangle(rightPoint, leftTopPoint, leftBottomPoint);
	return EngineGetModule(MeshFactory)->EndCreate();
}

// Create a textured quad mesh using the Beta Framework.
// Params:
//   textureSize = The UV size of the mesh, in texture coordinates.
//	 extents	 = The XY distance of the vertices from the origin.
// Returns:
//	 A pointer to the newly created mesh.
Mesh* CreateQuadMesh(const Vector2D& textureSize, const Vector2D& extents)
{
	Vertex topRight = Vertex(Vector2D(0.5f + extents.x, 0.5f + extents.y), textureSize);
	Vertex topLeft = Vertex(Vector2D(-0.5f + extents.x, 0.5f + extents.y), textureSize);
	Vertex bottomRight = Vertex(Vector2D(0.5f + extents.x, -0.5f + extents.y), textureSize);
	Vertex bottomLeft = Vertex(Vector2D(-0.5f + extents.x, -0.5f + extents.y), textureSize);

	EngineGetModule(MeshFactory)->AddTriangle(topRight, topLeft, bottomLeft);
	EngineGetModule(MeshFactory)->AddTriangle(bottomLeft, bottomRight, topLeft);
	return EngineGetModule(MeshFactory)->EndCreate();
}

//------------------------------------------------------------------------------