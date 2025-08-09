#pragma once

#include <cstdint>
#include <string>
#include <Cabrankengine/Core/Core.h>

namespace cabrankengine {

	// Enum class representing different image formats for textures.
	enum class ImageFormat {
		None = 0,
		R8,
		RGB8,
		RGBA8,
		RGBA32F
	};

	// Struct representing the specifications for a texture construction.
	struct TextureSpecification {
		uint32_t Width = 1;
		uint32_t Height = 1;
		ImageFormat Format = ImageFormat::RGBA8;
		bool GenerateMips = true;
	};

	// Interface base class representing a texture in the rendering system.
	class Texture {
		public:
			virtual ~Texture() = default;

			// Returns the specification of the texture, which includes its width, height, format, and mip generation status.
			virtual const TextureSpecification& getSpecification() const = 0;

			// Returns the texture width
			virtual uint32_t getWidth() const = 0;

			// Returns the texture height
			virtual uint32_t getHeight() const = 0;

			// Returns the texture's renderer ID, which is used by the graphics API to identify the texture.
			virtual uint32_t getRendererID() const = 0;

			// Returns the path to the texture file.
			virtual const std::string& getPath() const = 0;

			// Sets the texture data from a raw data pointer and size.
			virtual void setData(void* data, uint32_t size) = 0;

			// Binds the texture to a specific slot in the graphics API, allowing it to be used in rendering.
			virtual void bind(uint32_t slot = 0) const = 0;

			// Returns whether the texture is loaded successfully.
			virtual bool isLoaded() const = 0;

			// Returns whether both textures are equal based on their specifications and renderer IDs.
			virtual bool operator==(const Texture& other) const = 0;
	};

	// Texture2D is a derived class from Texture that represents a 2D texture in the rendering system.
	class Texture2D : public Texture {
		public:
			// Creates a new Texture2D instance with the specified texture specifications.
			static Ref<Texture2D> create(const TextureSpecification& specification);

			// Creates a new Texture2D instance from a file path.
			static Ref<Texture2D> create(const std::string& path);
	};
}
