#version 140

in vec3 coord;
in vec2 st;
in vec3 norm;

out vec4 light;
out vec2 fst;

uniform mat4 m;
uniform mat4 v;
uniform mat4 proj;

uniform vec4 ambient_mat;
uniform vec4 diffuse_mat;
uniform vec4 specular_mat;
uniform float shine;

uniform vec4 light1;
uniform vec4 light1_ambient;
uniform vec4 light1_diffuse;
uniform vec4 light1_specular;

void main() {
  mat4 vm = v * m;
  gl_Position = proj * vm * vec4(coord, 1.0);
  fst = st;

  vec3 normal = normalize(transpose(inverse(mat3(vm))) * norm);

   // vector towards the eye from the vertex position
   vec4 position4 = v * m * vec4(coord, 1.0);
   vec3 position = -normalize(position4.xyz);

   vec3 o;
   if (light1.w == 0.0)
      o = normalize(light1.xyz);
   else
      o = normalize(light1.xyz - position);
   vec4 l4 = v * vec4(o.xyz, 0.0);
   o = normalize(l4.xyz);

  // halfway vector
   vec3 halfway = normalize(position + o);

   // ambient reflection
   vec4 ambient = ambient_mat * light1_ambient;

   // diffuse reflection
   float diffuseAttenuation = max(dot(o, normal), 0.0);
   vec4 diffuse =  diffuseAttenuation * diffuse_mat * light1_diffuse;

   // specular reflection
   vec4 specular = vec4(0.0, 0.0, 0.0, 0.0);
   if (diffuseAttenuation > 0.0) {
      float specularAttenuation = 0.0;
      float spec = max(dot(normal, halfway), 0.0);
      if (spec > 0.0)
         specularAttenuation = pow(spec, shine);
      specular = max(specularAttenuation * specular_mat * light1_specular, 0.0);
   }

   // color of this vertex
   vec3 color3 = vec3(0.0, 0.0, 0.0);
   color3 += ambient.xyz;
   color3 += diffuse.xyz;
   color3 += specular.xyz;
   light = vec4(color3, 1.0);
}
