#pragma once

#include <memory>
#include <string>
#include <cstdint>
#include <Cabrankengine/Core/Core.h>

namespace cabrankengine {

	enum class ImageFormat {
		None = 0,
		R8,
		RGB8,
		RGBA8,
		RGBA32F
	};

	struct TextureSpecification {
		uint32_t Width = 1;
		uint32_t Height = 1;
		ImageFormat Format = ImageFormat::RGBA8;
		bool GenerateMips = true;
	};

	class Texture {
	public:
		virtual ~Texture() = default;

		virtual const TextureSpecification& getSpecification() const = 0;

		virtual uint32_t getWidth() const = 0;
		virtual uint32_t getHeight() const = 0;
		virtual uint32_t getRendererID() const = 0;

		virtual const std::string& getPath() const = 0;

		virtual void setData(void* data, uint32_t size) = 0;

		virtual void bind(uint32_t slot = 0) const = 0;

		virtual bool isLoaded() const = 0;

		virtual bool operator==(const Texture& other) const = 0;
	};

	class Texture2D : public Texture {
	public:
		static Ref<Texture2D> create(const TextureSpecification& specification);
		static Ref<Texture2D> create(const std::string& path);
	};
}
