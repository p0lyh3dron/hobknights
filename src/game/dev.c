#include "dev.h"

#include "../base/base.h"

#include "entity.h"
#include "shader.h"

#define FAST_OBJ_IMPLEMENTATION

#include "fast_obj.h"

image_t *_dev_image = (image_t *)0x0;

/*
 *    Create a developer cube entity with a model and transform.
 *
 *    @param float size     The size of the cube.
 *
 *    @return unsigned int    The entity ID of the cube.
 */
unsigned int dev_cube_create(float size) {
    vertex_t verts[36] = {
        {{-size, -size, -size, 1.f}, {0.f, 0.f}},
        {{-size, +size, -size, 1.f}, {0.f, 1.f}},
        {{+size, +size, -size, 1.f}, {1.f, 1.f}},
        {{-size, -size, -size, 1.f}, {0.f, 0.f}},
        {{+size, -size, -size, 1.f}, {1.f, 0.f}},
        {{+size, +size, -size, 1.f}, {1.f, 1.f}},

        {{-size, -size, +size, 1.f}, {0.f, 0.f}},
        {{-size, +size, +size, 1.f}, {0.f, 1.f}},
        {{+size, +size, +size, 1.f}, {1.f, 1.f}},
        {{-size, -size, +size, 1.f}, {0.f, 0.f}},
        {{+size, -size, +size, 1.f}, {1.f, 0.f}},
        {{+size, +size, +size, 1.f}, {1.f, 1.f}},

        {{-size, -size, +size, 1.f}, {0.f, 0.f}},
        {{-size, +size, +size, 1.f}, {0.f, 1.f}},
        {{-size, +size, -size, 1.f}, {1.f, 1.f}},
        {{-size, -size, +size, 1.f}, {0.f, 0.f}},
        {{-size, -size, -size, 1.f}, {1.f, 0.f}},
        {{-size, +size, -size, 1.f}, {1.f, 1.f}},

        {{+size, -size, +size, 1.f}, {0.f, 0.f}},
        {{+size, +size, +size, 1.f}, {0.f, 1.f}},
        {{+size, +size, -size, 1.f}, {1.f, 1.f}},
        {{+size, -size, +size, 1.f}, {0.f, 0.f}},
        {{+size, -size, -size, 1.f}, {1.f, 0.f}},
        {{+size, +size, -size, 1.f}, {1.f, 1.f}},

        {{-size, -size, -size, 1.f}, {0.f, 0.f}},
        {{-size, -size, +size, 1.f}, {0.f, 1.f}},
        {{+size, -size, +size, 1.f}, {1.f, 1.f}},
        {{-size, -size, -size, 1.f}, {0.f, 0.f}},
        {{+size, -size, -size, 1.f}, {1.f, 0.f}},
        {{+size, -size, +size, 1.f}, {1.f, 1.f}},

        {{-size, +size, -size, 1.f}, {0.f, 0.f}},
        {{-size, +size, +size, 1.f}, {0.f, 1.f}},
        {{+size, +size, +size, 1.f}, {1.f, 1.f}},
        {{-size, +size, -size, 1.f}, {0.f, 0.f}},
        {{+size, +size, -size, 1.f}, {1.f, 0.f}},
        {{+size, +size, +size, 1.f}, {1.f, 1.f}},
    };

    if (_dev_image == (image_t *)0x0)
        _dev_image = image_create_from_file("assets/images/dev/noise.bmp", 69);

    model_t *model = model_create_textured(&verts, sizeof(verts), sizeof(verts[0]), _v_layout, _dev_image);

    unsigned int entity = entity_create();
    entity_add_transform(entity, nullptr, nullptr);
    entity_add_model(entity, model);

    return entity;
}

/*
 *    Create a developer plane entity with a model and transform.
 *
 *    @param float size     The size of the plane.
 * 
 *    @return unsigned int    The entity ID of the plane.
 */
unsigned int dev_plane_create(float size) {
    vertex_t verts[6] = {
        {{-size, 0.f, -size, 1.f}, {0.f, 0.f}},
        {{-size, 0.f, +size, 1.f}, {0.f, 1.f}},
        {{+size, 0.f, +size, 1.f}, {1.f, 1.f}},
        {{-size, 0.f, -size, 1.f}, {0.f, 0.f}},
        {{+size, 0.f, -size, 1.f}, {1.f, 0.f}},
        {{+size, 0.f, +size, 1.f}, {1.f, 1.f}},
    };

    if (_dev_image == (image_t *)0x0)
        _dev_image = image_create_from_file("assets/images/dev/noise.bmp", 69);

    model_t *model = model_create_textured(&verts, sizeof(verts), sizeof(verts[0]), _v_layout, _dev_image);

    unsigned int entity = entity_create();
    entity_add_transform(entity, nullptr, nullptr);
    entity_add_model(entity, model);

    return entity;
}

#define SCALE 0.03f;

unsigned int dev_riverhouse() {
    fastObjMesh *pMesh = fast_obj_read( "/home/p0ly/Downloads/c1a0.obj" );
    if ( pMesh == NULL ) {
        return 0;
    }
	
    // chik_vertex_t *pVerts = ( chik_vertex_t * )malloc( pMesh->position_count * 3 * sizeof( chik_vertex_t ) );
    vertex_t *pVerts = ( vertex_t * )malloc( pMesh->index_count * 3 * sizeof( vertex_t ) );
    if ( pVerts == NULL ) {
        free( pMesh );
        return 0;
    }
	
	u32 vertIndex = 0;
    u32 totalIndexOffset = 0;
	
	for ( u32 objIndex = 0; objIndex < pMesh->object_count; objIndex++ )
	{
		fastObjGroup group = pMesh->objects[objIndex];
		
		for ( u32 faceIndex = 0; faceIndex < group.face_count; faceIndex++ )
		{
			u32 faceVertCount = pMesh->face_vertices[group.face_offset + faceIndex];
			u32 faceMat = pMesh->face_materials[group.face_offset + faceIndex];
			
			for ( u32 faceVertIndex = 0; faceVertIndex < faceVertCount; faceVertIndex++ )
			{
				// NOTE: mesh->indices holds each face "fastObjIndex" as three
				// seperate index objects contiguously laid out one after the other
				// fastObjIndex objIndex = obj->indices[totalIndexOffset + faceVertIndex];
				fastObjIndex objIndex = pMesh->indices[totalIndexOffset + faceVertIndex];

				// TODO: probably realloc pVerts to a higher amount if faceVertCount is 4
				if ( faceVertIndex >= 3 )
				{
					// TODO: once you do that realloc,
					// then add dup verts in this order:
					
					// auto ind0 = object->ind[ object->ind.size() - 3 ];
					// auto ind1 = object->ind[ object->ind.size() - 1 ];
					// 
					// object->ind.push_back( ind0 );
					// object->ind.push_back( ind1 );
					// 
					// object->vert.push_back( object->vert[ind0] );
					// object->vert.push_back( object->vert[ind1] );
					// 
					// verts.push_back( object->vert[ind0] );
					// verts.push_back( object->vert[ind1] );
					// 
					// totalVerts += 2;
					
					// for now, just skip them
					// vertIndex += 3;
					
					pVerts[ vertIndex ].pos.x = 0.f;
					pVerts[ vertIndex ].pos.y = 0.f;
					pVerts[ vertIndex ].pos.z = 0.f;
				
					vertIndex++;
					continue;
				}

				const u32 position_index = objIndex.p * 3;
				const u32 texcoord_index = objIndex.t * 2;
				const u32 normal_index   = objIndex.n * 3;

				pVerts[ vertIndex ].pos.x = pMesh->positions[ position_index ] * SCALE;
				pVerts[ vertIndex ].pos.y = pMesh->positions[ position_index + 1 ] * -SCALE;
				pVerts[ vertIndex ].pos.z = pMesh->positions[ position_index + 2 ] * SCALE;
                pVerts[ vertIndex ].pos.w = 1;

				// vert.normal.x = pMesh->normals[normal_index];
				// vert.normal.y = pMesh->normals[normal_index + 1];
				// vert.normal.z = pMesh->normals[normal_index + 2];
				
				pVerts[ vertIndex ].tex.x = pMesh->texcoords[texcoord_index] * 4;
				pVerts[ vertIndex ].tex.y = ( 1.0f - pMesh->texcoords[texcoord_index + 1] ) * 4;
				
				// pVerts[ i ].aColor = ( color32_t ){ rand() % 255, rand() % 255, rand() % 255, 255 };
				
				vertIndex++;
			}

            totalIndexOffset += faceVertCount;
		}
	}

    if (_dev_image == (image_t *)0x0)
        _dev_image = image_create_from_file("assets/images/dev/noise.bmp", 69);

    model_t *model = model_create_textured(pVerts, sizeof( vertex_t ) * pMesh->index_count, sizeof(vertex_t), _v_layout, _dev_image);

    unsigned int entity = entity_create();
    entity_add_transform(entity, nullptr, nullptr);
    entity_add_model(entity, model);

    fast_obj_destroy( pMesh );

    return entity;
}