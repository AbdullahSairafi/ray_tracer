#ifndef OBJ_LOADER_H
#define OBJ_LOADER_H

//STD Libs
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cassert>
// own libs
#include <vector.h>
#include <shapes.h>

void load_obj_file(const char *filename, vector<Vertex> &vertices, vector<Vec3i> &faces){
    // make sure filename is not null 
    assert(filename);
    // open file
    ifstream in_file(filename);
    // error handling
    if(!in_file){
        cerr << "Error: could not open " << filename << endl;
        exit(-1);
    }

    // read file 

    stringstream ss;
    string line;
    string prefix;

    // vectors to store file info
    vector<Vec3d> verts_positions;
    vector<Vec2d> tex_coords;
    vector<Vec3d> verts_normals;

    
    while(getline(in_file, line)){
        // get the prefix
        ss.str(""); // empty buffer
        ss.clear(); // reset error flags
        ss.str(line);
        ss >> prefix;

        // process the line
        switch (prefix){
        case "#":
            // do nothing
            break;
        case "o":
            // do nothing
            break;
        case "s":
            // do nothing
            break;
        case "usemtl": // add material TODO later
            // do nothing
            break;
        case "v":
            string x, y, z;
            ss >> x >> y >> z;
            verts_positions.push_back(Vec3d(stod(x), stod(y), stod(z)));
            break;
        case "vt":
            string x, y;
            ss >> x >> y;
            Vec2d temp;
            temp.x = stod(x);
            temp.y = stod(y);
            tex_coords.push_back(temp);
            break;
        case "vn":
            string x, y, z;
            ss >> x >> y >> z;
            verts_normals.push_back(Vec3d(stod(x), stod(y), stod(z)));
            break;
        case "f": //TODO: triangulation must be processed here aka fill up faces vec
            //only take format: 
            // f v/vt/vn ...
            int counter = 0;
            int temp;

            // vectors to store file info indices
            vector<int> verts_indices;
            vector<int> texcoords_indices;
            vector<int> normals_indices;

            // read the verices indcies
			while (ss >> temp)
			{
				//Pushing indices into correct arrays
				if (counter == 0)
					verts_indices.push_back(temp);
				else if (counter == 1)
					texcoords_indices.push_back(temp);
				else if (counter == 2)
					normals_indices.push_back(temp);

				//Handling characters
				if (ss.peek() == '/')
				{
					++counter;
					ss.ignore(1, '/');
				}
				else if (ss.peek() == ' ')
				{
					++counter;
					ss.ignore(1, ' ');
				}

				//Reset the counter
				if (counter > 2)
					counter = 0;
			}
            

            // triangulate the face and push indices into faces vector
            int num_face_tris = verts_indices.size() - 2; // num verts per face - 2;
            for(int i = 0; i < num_face_tris; i++){
                Vec3i triangle;
                triangle.v[0] = verts_indices[0] - 1; // note -1 is because the vertices start from 1 instead of 0
                triangle.v[1] = verts_indices[i+1] - 1;
                triangle.v[2] = verts_indices[i+2] - 1;
                faces.push_back(triangle);
            }

            // build vertices:
            for(size_t i = 0; i < verts_indices.size(); i++){
                Vertex temp_vertex;
                // note -1 is because the vertices start from 1 instead of 0
                temp_vertex.position = verts_positions[verts_indices[i]-1]; 
                temp_vertex.normal = verts_normals[normals_indices[i]-1];
                temp_vertex.tex_coord = tex_coords[texcoords_indices[i]-1];
                vertices.push_back(temp_vertex);
            }

            break;
        
        default:
            break;
        }
    }

}
#endif