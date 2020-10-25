#include <GL/freeglut.h>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL 
#include <glm/gtx/component_wise.hpp>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdlib.h>

struct Vertex
{
    glm::vec3 position;
    glm::vec2 texcoord;
    glm::vec3 normal;
};

struct VertRef
{
    VertRef( int v, int vt, int vn ) : v(v), vt(vt), vn(vn) { }
    int v, vt, vn;
};

std::vector< Vertex > LoadOBJ( std::istream& in )
{
    std::vector< Vertex > verts;

    std::vector< glm::vec4 > positions( 1, glm::vec4( 0, 0, 0, 0 ) );
    std::vector< glm::vec3 > texcoords( 1, glm::vec3( 0, 0, 0 ) );
    std::vector< glm::vec3 > normals( 1, glm::vec3( 0, 0, 0 ) );
    std::string lineStr;
    while( std::getline( in, lineStr ) )
    {
        std::istringstream lineSS( lineStr );
        std::string lineType;
        lineSS >> lineType;
		
		// mtl
        if( lineType == "mtllib" )
        {
		    lineSS >> MTLNAME;
            LoadMTL();
        }
        // usemtl
        if( lineType == "usemtl" )
        {
            lineSS >> USEMTL;
            printf("\nUSEMTL: %s\n", USEMTL);
        //    LoadMTL();
        }
		
        // vertex
        if( lineType == "v" )
        {
            float x = 0, y = 0, z = 0, w = 1;
            lineSS >> x >> y >> z >> w;
            positions.push_back( glm::vec4( x, y, z, w ) );
        }

        // texture
        if( lineType == "vt" )
        {
            float u = 0, v = 0, w = 0;
            lineSS >> u >> v >> w;
            texcoords.push_back( glm::vec3( u, v, w ) );
        }

        // normal
        if( lineType == "vn" )
        {
            float i = 0, j = 0, k = 0;
            lineSS >> i >> j >> k;
            normals.push_back( glm::normalize( glm::vec3( i, j, k ) ) );
        }

        // polygon
        if( lineType == "f" )
        {
            std::vector< VertRef > refs;
            std::string refStr;
            while( lineSS >> refStr )
            {
                std::istringstream ref( refStr );
                std::string vStr, vtStr, vnStr;
                std::getline( ref, vStr, '/' );
                std::getline( ref, vtStr, '/' );
                std::getline( ref, vnStr, '/' );
                int v = atoi( vStr.c_str() );
                int vt = atoi( vtStr.c_str() );
                int vn = atoi( vnStr.c_str() );
                v  = (  v >= 0 ?  v : positions.size() +  v );
                vt = ( vt >= 0 ? vt : texcoords.size() + vt );
                vn = ( vn >= 0 ? vn : normals.size()   + vn );
                refs.push_back( VertRef( v, vt, vn ) );
            }

            // triangulate, assuming n>3-gons are convex and coplanar
            for( size_t i = 1; i+1 < refs.size(); ++i )
            {
                const VertRef* p[3] = { &refs[0], &refs[i], &refs[i+1] };
				
                // http://www.opengl.org/wiki/Calculating_a_Surface_Normal
                glm::vec3 U( positions[ p[1]->v ] - positions[ p[0]->v ] );
                glm::vec3 V( positions[ p[2]->v ] - positions[ p[0]->v ] );
                glm::vec3 faceNormal = glm::normalize( glm::cross( U, V ) );

                for( size_t j = 0; j < 3; ++j )
                {
                    Vertex vert;
                    vert.position = glm::vec3( positions[ p[j]->v ] );
                    vert.texcoord = glm::vec2( texcoords[ p[j]->vt ] );
                    vert.normal = ( p[j]->vn != 0 ? normals[ p[j]->vn ] : faceNormal );
                    verts.push_back( vert );
                }
            }
        }
    }

    return verts;
}

bool Loaded = false;

std::vector< Vertex > model;
void DrawOBJ()
{
		/**** Set Material ****/
		glDisable(GL_COLOR_MATERIAL);
		float MatAmbient[] = { KA[0], KA[1], KA[2], D };
		float MatDiffuse[] = { KD[1], KD[2], KD[3], D };
		float MatSpecular[] = { KS[0], KS[1], KS[2], 0.1f };
		float MatShininess = 60;
		float MatEmissive[] = {KE[0], KE[1], KE[2], 1.0f};
		
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MatAmbient);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MatDiffuse);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, MatSpecular);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, MatShininess);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, MatEmissive);
		
        glEnableClientState( GL_VERTEX_ARRAY );
        glEnableClientState( GL_TEXTURE_COORD_ARRAY );
        glEnableClientState( GL_NORMAL_ARRAY );

		glVertexPointer( 3, GL_FLOAT, sizeof(Vertex), &model[0].position );
		glTexCoordPointer( 2, GL_FLOAT, sizeof(Vertex), &model[0].texcoord );
		glNormalPointer( GL_FLOAT, sizeof(Vertex), &model[0].normal ); 
	        
        glDrawArrays( GL_TRIANGLES, 0, model.size() );
        
        glDisableClientState( GL_VERTEX_ARRAY );
        glDisableClientState( GL_TEXTURE_COORD_ARRAY );
        glDisableClientState( GL_NORMAL_ARRAY );
        /**** Reset Material ****/
        float MatAmbient1[] = { 1.0, 1.0, 1.0, 1.0f };
		float MatDiffuse1[] = { 1.0, 1.0, 1.0, 1.0f };
		float MatSpecular1[] = {1.0, 1.0, 1.0, 0.1f };
		float MatShininess1 = 60;
		float MatEmissive1[] = {0.0, 0.0, 0.0, 1.0f};
		
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MatAmbient1);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MatDiffuse1);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, MatSpecular1);
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, MatShininess1);
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, MatEmissive1);
        glEnable(GL_COLOR_MATERIAL);
}
