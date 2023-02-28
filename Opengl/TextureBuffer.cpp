#include"TextureBuffer.h"


TextureBuffer::TextureBuffer(int count)
{

    // load and create a texture 
   // -------------------------
    glGenTextures(1, &m_iTextureBufferId);
   

}
TextureBuffer::~TextureBuffer()
{
    glDeleteTextures(1,&m_iTextureBufferId);

}

void TextureBuffer::LoadImage(const char* path)
{
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
   // const char* path = "../wang.jpg";
    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

}
void  TextureBuffer::UseImage()
{

}
void TextureBuffer::Bind()
{
    glBindTexture(GL_TEXTURE_2D, m_iTextureBufferId); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object

     // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

}
void TextureBuffer::UnBind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}