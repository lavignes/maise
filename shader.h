/**
 * shader.h: Classes for managing shaders
 * @author Scott LaVigne
 */
#ifndef SHADER_H
#define SHADER_H

#include <string>

#include <GL/gl.h>

/**
 * A shader manager.
 */
class Pipeline {
  public:

    /**
     * Generic shader object
     */
    class Shader {
      public:
        /**
         * Shader types
         */
        enum Type {
          VERTEX = GL_VERTEX_SHADER,
          FRAGMENT = GL_FRAGMENT_SHADER
        };

        /**
         * Compile a shader.
         * @param type the type of shader
         * @param path location of GLSL shader file
         */
        Shader(Type type, const std::string& path);

        /**
         * Destructor.
         * Releases the OpenGL shader resource
         */
        virtual ~Shader();

        /**
         * Get OpenGL id for shader.
         * @return the id
         */
        unsigned get_id() const;

        /**
         * Get shader type.
         * @return the shader type
         */
        Type get_type() const;

      protected:
        unsigned id;
        Type type;
    };

    /**
     * Link and transmit GLSL program.
     * Shaders passed in are owned by the instance, and thus will be freed.
     * @param vertex   a vertex shader object
     * @param fragment a fragment shader object
     * @param slots    number of slots for binding attributes/uniforms
     */
    Pipeline(const Shader* vertex, const Shader* fragment, unsigned slots = 16);
    Pipeline(const std::string& vert_path, const std::string& frag_path,
        unsigned slots = 16);

    /**
     * Destructor.
     * Frees attached shaders and releases OpenGL program resources.
     */
    virtual ~Pipeline();

    /**
     * Locate and bind an attribute in the program.
     * @param attr_name an attribute name
     * @param slot      location to bind the attribute to
     */
    void bind_attribute(const std::string& attr_name, unsigned slot);

    /**
     * Locate and bind a uniform in the program.
     * @param unif_name a uniform name
     * @param slot      location bind the uniform to
     */
    void bind_uniform(const std::string& unif_name, unsigned slot);

    /**
     * Return OpenGL resource id for the program.
     * @return the id
     */
    unsigned get_id() const;

    /**
     * Get location of bound attribute in slot.
     * This simulates layout specifiers not present in older versions
     * of OpenGL.
     * @param  slot a previously bound slot
     * @return      the OpenGL resource id for that attribute
     */
    unsigned get_attribute(unsigned slot) const;
    
    /**
     * Get location of bound uniform in slot.
     * This simulates layout specifiers not present in older versions
     * of OpenGL.
     * @param  slot a previously bound slot
     * @return      the OpenGL resource id for that uniform
     */
    unsigned get_uniform(unsigned slot) const;

  protected:
    void link(unsigned);
    unsigned id;
    unsigned* attributes;
    unsigned* uniforms;
    const Shader* vert_shader;
    const Shader* frag_shader;
};

#endif // SHADER_H
