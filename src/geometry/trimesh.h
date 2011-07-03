/*
 * filename :	trimesh.h
 *
 * programmer :	Cao Jiayin
 */

#ifndef	SORT_TRIMESH
#define	SORT_TRIMESH

// include the headers
#include <vector>
#include "primitive.h"
#include "utility/referencecount.h"
#include "managers/meshmanager.h"
#include "geometry/transform.h"

//////////////////////////////////////////////////////////////////////////////////
//	definition of trimesh
class TriMesh
{
// public method
public:
	// default constructor
	TriMesh();
	// destructor
	~TriMesh();

	// load the mesh from file
	// para 'str'  : the name of the input file
	// para 'transform' : the transformation of the mesh
	// para 'type' : the type of the mesh file , default value is obj
	// result      : 'true' if loading is successful
	bool LoadMesh( const string& str , Transform& transform );

	// fill buffer into vector
	// para 'vec' : the buffer to filled
	void FillTriBuf( vector<Primitive*>& vec );

// private field
public:
	// the memory for the mesh
	Reference<BufferMemory> m_pMemory;

	// the tranformation of the mesh
	Transform		m_Transform;

	// whether the mesh is instanced
	bool			m_bInstanced;

// private method
	// initialize default data
	void	_init();

	// generate normal for the triangle mesh
	void	_genFlatNormal();
	void	_genSmoothNormal();

// set friend class
friend	class	MeshManager;
friend	class	Triangle;
};

#endif