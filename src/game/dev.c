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

typedef struct {
    vertex_t* verts;
    u32       vert_count;
    u32       mat_index;
} mat_vertex_list_t;

unsigned int dev_load_obj_entity(const char *path, float scale, float x_rot, float y_rot) {
    fastObjMesh *pMesh = fast_obj_read(path);
    if ( pMesh == NULL ) {
        VLOGF_ERR("Failed to Load Obj: %s\n", path);
        return 0;
    }

    u32 mat_count = MAX(1, pMesh->material_count);

    mat_vertex_list_t* mat_vertex_list = (mat_vertex_list_t*)malloc(mat_count * sizeof(mat_vertex_list_t));
    
    for (unsigned int i = 0; i < mat_count; i++) {
        mat_vertex_list[i].mat_index  = i;
        mat_vertex_list[i].vert_count = 0;
    
        // TODO: THIS OVERALLOCATES WAY TOO MUCH !!!
        mat_vertex_list[i].verts = (vertex_t*)calloc(pMesh->index_count, sizeof(vertex_t) * 3);
    }

    material_t* temp_mats = calloc(mat_count, sizeof(material_t));

    if (_dev_image == (image_t*)0x0)
        _dev_image = image_create_from_file("assets/images/dev/noise.bmp", 69);

    if (pMesh->material_count == 0) {
        temp_mats[0].albedo = _dev_image;
    }

    for (unsigned int i = 0; i < pMesh->material_count; i++) {
        fastObjMaterial obj_mat = pMesh->materials[i];

        printf("Material %d: %s\n", i, obj_mat.name ? obj_mat.name : "unnamed");

        // diffuse texture
        if (obj_mat.map_Kd.path)
            temp_mats[i].albedo = image_create_from_file(obj_mat.map_Kd.path, 69);
        else
            temp_mats[i].albedo = _dev_image;

        if (obj_mat.map_Ke.path)
            temp_mats[i].emission = image_create_from_file(obj_mat.map_Ke.path, 69);

        if (obj_mat.map_Ka.path)
            temp_mats[i].ambient_occlusion = image_create_from_file(obj_mat.map_Ka.path, 69);
    }
	
	u32 vertIndex = 0;
    u32 totalIndexOffset = 0;

    // STORE FACE MATS FOR VERTICES HERE
	
	for ( u32 objIndex = 0; objIndex < pMesh->object_count; objIndex++ )
	{
		fastObjGroup group = pMesh->objects[objIndex];
		
		for ( u32 faceIndex = 0; faceIndex < group.face_count; faceIndex++ )
		{
			u32 faceVertCount = pMesh->face_vertices[group.face_offset + faceIndex];
            u32 faceMat = 0;

            if (pMesh->material_count > 0) {
                faceMat = pMesh->face_materials[group.face_offset + faceIndex];
            }
			
			for ( u32 faceVertIndex = 0; faceVertIndex < faceVertCount; faceVertIndex++ )
			{
				// NOTE: mesh->indices holds each face "fastObjIndex" as three
				// seperate index objects contiguously laid out one after the other
				// fastObjIndex objIndex = obj->indices[totalIndexOffset + faceVertIndex];
				fastObjIndex objIndex = pMesh->indices[totalIndexOffset + faceVertIndex];

				// TODO: probably realloc pVerts to a higher amount if faceVertCount is 4
				if ( faceVertIndex >= 3 )
					continue;

				const u32 position_index = objIndex.p * 3;
				const u32 texcoord_index = objIndex.t * 2;
				const u32 normal_index   = objIndex.n * 3;

				mat_vertex_list[ faceMat ].verts[ mat_vertex_list[faceMat].vert_count ].pos.x = pMesh->positions[ position_index ] * scale;
				mat_vertex_list[ faceMat ].verts[ mat_vertex_list[faceMat].vert_count ].pos.y = pMesh->positions[ position_index + 1 ] * -scale;
				mat_vertex_list[ faceMat ].verts[ mat_vertex_list[faceMat].vert_count ].pos.z = pMesh->positions[ position_index + 2 ] * -scale;
                mat_vertex_list[ faceMat ].verts[ mat_vertex_list[faceMat].vert_count ].pos.w = 1;

				// vert.normal.x = pMesh->normals[normal_index];
				// vert.normal.y = pMesh->normals[normal_index + 1];
				// vert.normal.z = pMesh->normals[normal_index + 2];
				
				mat_vertex_list[ faceMat ].verts[ mat_vertex_list[faceMat].vert_count ].tex.x = pMesh->texcoords[texcoord_index];
				mat_vertex_list[ faceMat ].verts[ mat_vertex_list[faceMat].vert_count ].tex.y = pMesh->texcoords[texcoord_index + 1];

                mat_vertex_list[faceMat].vert_count++;
				
				// pVerts[ i ].aColor = ( color32_t ){ rand() % 255, rand() % 255, rand() % 255, 255 };
				
				vertIndex++;
			}

            totalIndexOffset += faceVertCount;
		}
	}

    // merge them all to a list
    vertex_t* verts = calloc(pMesh->index_count, sizeof(vertex_t) * 3);

    u32 vi = 0, m = 0;
    for (; m < mat_count; m++) {
        for (u32 i = 0; i < mat_vertex_list[m].vert_count; i++) {

            // if ( m == 0 )
                verts[vi] = mat_vertex_list[m].verts[i];

            vi++;
        }
    }

    // model_t *model = model_create_textured(pVerts, sizeof( vertex_t ) * pMesh->index_count, sizeof(vertex_t), _v_layout, _dev_image);
    model_t *model = model_create(verts, sizeof( vertex_t ) * pMesh->index_count, sizeof(vertex_t), _v_layout);

    mesh_set_surface_count(model->mesh, mat_count);
    
    // write stuff to materials
    u32 offset = 0;
    for (u32 m = 0; m < mat_count; m++) {
        // u32 m = 0;
        // m = mat_vertex_list[m].mat_index;
        mesh_set_surface_buffer_data(model->mesh, m, offset, mat_vertex_list[m].vert_count);

        material_t* mat = mesh_get_material(model->mesh, m);
        mat->albedo = temp_mats[m].albedo;
        mat->ambient_occlusion = temp_mats[m].ambient_occlusion;
        mat->emission = temp_mats[m].emission;

        mat->ambient_occlusion_power = temp_mats[m].ambient_occlusion_power;
        mat->emission_power = temp_mats[m].emission_power;

        offset += mat_vertex_list[m].vert_count;
    }

    unsigned int entity = entity_create();
    vec2_t rot;
    rot.x = x_rot * PI/180.f;
    rot.y = y_rot * PI/180.f;
    entity_add_transform(entity, nullptr, &rot);
    entity_add_model(entity, model);

    fast_obj_destroy(pMesh);
    free(temp_mats);

    for (unsigned int i = 0; i < mat_count; i++) {
        free(mat_vertex_list[i].verts);
    }

    free(mat_vertex_list);

    return entity;
}

unsigned int dev_riverhouse() {
    // return dev_load_obj_entity("hobknights/assets/c1a0.obj", 0.01f, 0.f, 0.f);
    return dev_load_obj_entity("hobknights/assets/riverhouse_v1.obj", 1.f, -90.f, 0.f);
    // return dev_load_obj_entity("hobknights/assets/riverhouse_v1_tmp3.obj", 1.f, 0.f, 0.f);
    // return dev_load_obj_entity("hobknights/assets/protogen_27.obj", 5.f, -90.f, 0.f);
    // return dev_load_obj_entity("hobknights/assets/funny.obj", 1.f, 0.f, 0.f);
    // return dev_load_obj_entity("D:\\projects\\chocolate\\dev\\output\\sidury\\models\\riverhouse\\riverhouse_v1_tmp2.obj", 1.f, 0.f, 0.f);
}

