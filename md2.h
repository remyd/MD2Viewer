//
//	md2.h - header file
//



#ifndef		MD2_H
#define		MD2_H


// magic number "IDP2" or 844121161
#define MD2_ID				(('2'<<24) + ('P'<<16) + ('D'<<8) + 'I')

// model version
#define	MD2_VERSION				8

// maximum number of vertices for a MD2 model
#define MAX_MD2_VERTS			2048

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include	<fstream>



typedef float vec3_t[3];



// md2 header
typedef struct
{
	int		id;					// magic number. must be equal to "IPD2"
	int		version;			// md2 version. must be equal to 8

	int		skinwidth;			// width of the texture
	int		skinheight;			// height of the texture
	int		framesize;			// size of one frame in bytes

	int		num_skins;			// number of textures
	int		num_xyz;			// number of vertices
	int		num_st;				// number of texture coordinates
	int		num_tris;			// number of triangles
	int		num_glcmds;			// number of opengl commands
	int		num_frames;			// total number of frames

	int		ofs_skins;			// offset to skin names (64 bytes each)
	int		ofs_st;				// offset to s-t texture coordinates
	int		ofs_tris;			// offset to triangles
	int		ofs_frames;			// offset to frame data
	int		ofs_glcmds;			// offset to opengl commands
	int		ofs_end;			// offset to the end of file

} md2_t;


typedef struct
{
	short u,v;
} tex_coord;


// triangle
typedef struct
{
    short   index_xyz[3];    // indexes to triangle's vertices
    short   index_st[3];     // indexes to vertices' texture coorinates

} triangle_t;

// vertex
typedef struct
{
	unsigned char	v[3];				// compressed vertex' (x, y, z) coordinates
	unsigned char	lightnormalindex;	// index to a normal vector for the lighting

} vertex_t;



// frame
typedef struct
{
	float		scale[3];		// scale values
	float		translate[3];	// translation vector
	char		name[16];		// frame name
	vertex_t	verts[1];		// first vertex of this frame

} frame_t;



// animation
typedef struct
{
	int		first_frame;			// first frame of the animation
	int		last_frame;				// number of frames
	int		fps;					// number of frames per second

} anim_t;



// animation list
typedef enum {
	STAND,
	RUN,
	ATTACK,
	PAIN_A,
	PAIN_B,
	PAIN_C,
	JUMP,
	FLIP,
	SALUTE,
	FALLBACK,
	WAVE,
	POINT,
	CROUCH_STAND,
	CROUCH_WALK,
	CROUCH_ATTACK,
	CROUCH_PAIN,
	CROUCH_DEATH, 
	DEATH_FALLBACK,
	DEATH_FALLFORWARD,
	DEATH_FALLBACKSLOW,
	BOOM,

	MAX_ANIMATIONS

} animType_t;




// ==============================================
// CMD2Model - MD2 model class object.
// ==============================================

class MD2
{
public:
	// constructor/destructor
	MD2( void );
	virtual ~MD2( void );


	// functions
	bool	LoadModel( const char *filename );

//private:
	int				num_frames;			// number of frames
	int				num_xyz;			// number of vertices
	int				num_tris;			// number of triangles

	int				skin_width;
	int				skin_height;

	vec3_t			*m_vertices;		// vertex array
	tex_coord		*texs;
	triangle_t		*tris;

	static anim_t animlist[21];
};

inline MD2::MD2( void )
{
	m_vertices		= 0;
	num_frames		= 0;
	num_xyz			= 0;
	num_tris		= 0;
	texs			= 0;
	tris			= 0;
}

inline MD2::~MD2( void )
{
	if(m_vertices) delete [] m_vertices;
	if(texs) delete [] texs;
	if(tris) delete [] tris;
}

inline bool MD2::LoadModel( const char *filename )
{
	std::ifstream	file;			// file stream
	md2_t			header;			// md2 header
	char			*buffer;		// buffer storing frame data
	frame_t			*frame;			// temporary variable
	vec3_t			*ptrverts;		// pointer on m_vertices
	
	// try to open filename
	file.open( filename, std::ios::in | std::ios::binary );

	if( file.fail() )
		return false;

	// read header file
	file.read( (char *)&header, sizeof( md2_t ) );


	/////////////////////////////////////////////
	//		verify that this is a MD2 file

	// check for the ident and the version number

	if( (header.id != MD2_ID) && (header.version != MD2_VERSION) )
	{
		// this is not a MD2 model
		file.close();
		return false;
	}

	/////////////////////////////////////////////


	// initialize member variables
	num_frames	= header.num_frames;
	num_xyz		= header.num_xyz;
	num_tris	= header.num_tris;
	skin_width	= header.skinwidth;
	skin_height = header.skinheight;


	// allocate memory
	m_vertices		= new vec3_t[ num_xyz * num_frames ];
	buffer			= new char[ num_frames * header.framesize ];
	texs			= new tex_coord[header.num_st];
	tris			= new triangle_t[header.num_tris];


	/////////////////////////////////////////////
	//			reading file data

	// read tex coords...
	file.seekg(header.ofs_st,std::ios::beg);
	file.read((char *)texs,header.num_st*sizeof(tex_coord));

	// read tris info
	file.seekg(header.ofs_tris,std::ios::beg);
	file.read((char *)tris,header.num_tris*sizeof(triangle_t));

	// read frame data...
	file.seekg( header.ofs_frames, std::ios::beg );
	file.read( (char *)buffer, num_frames * header.framesize );

	/////////////////////////////////////////////


	// vertex array initialization
	for( int j = 0; j < num_frames; j++ )
	{
		// ajust pointers
		frame		= (frame_t *)&buffer[ header.framesize * j ];
		ptrverts	= &m_vertices[ num_xyz * j ];

		for( int i = 0; i < num_xyz; i++ )
		{
			ptrverts[i][0] = (frame->verts[i].v[0] * frame->scale[0]) + frame->translate[0];
			ptrverts[i][1] = (frame->verts[i].v[1] * frame->scale[1]) + frame->translate[1];
			ptrverts[i][2] = (frame->verts[i].v[2] * frame->scale[2]) + frame->translate[2];
		}
	}


	// free buffer's memory
	delete [] buffer;

	// close the file and return
	file.close();
	return true;
}

#endif	// MD2_H