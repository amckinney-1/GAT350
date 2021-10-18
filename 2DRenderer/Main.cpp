#include "Renderer.h"
#include "Framebuffer.h"
#include "PostProcess.h"
#include "Image.h"

#include <iostream>
#include <SDL.h>

int main(int, char**)
{
	const int WIDTH = 800;
	const int HEIGHT = 600;

	std::unique_ptr<Renderer> renderer = std::make_unique<Renderer>();
	renderer->Initialize(WIDTH, HEIGHT);
	
	std::unique_ptr<Framebuffer> framebuffer = std::make_unique<Framebuffer>(renderer.get(), renderer->width, renderer->height);

	bool quit = false;
	SDL_Event event;
	while (!quit)
	{
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}

		framebuffer->Clear({ 0, 0, 0, 255 });

        //for (int i = 0; i < 25; i++)
        //{
        //    framebuffer->DrawPoint(rand() % renderer->width, rand() % renderer->height, { 0, 255, 0, 0 });
        //}
        //for (int i = 0; i < 10; i++)
        //{
        //    framebuffer->DrawRect(rand() % renderer->width, rand() % renderer->height, 20, 20, { 0, 0, 255, 0 });
        //}
        //for (int i = 0; i < 10; i++)
        //{
        //    framebuffer->DrawLine(renderer->width >> 1, renderer->height >> 1, rand() % renderer->width, rand() % renderer->height, { 255, 255, 255, 0 });
        //}
        //for (int i = 0; i < 5; i++)
        //{
        //    framebuffer->DrawTriangle(rand() % renderer->width, rand() % renderer->height, rand() % renderer->width, rand() % renderer->height, rand() % renderer->width, rand() % renderer->height, { 255, 0, 0, 0 });
        //}
        ///*for (int i = 0; i < 1; i++)
        //{
        //    framebuffer->DrawCircle(rand() % renderer->width, rand() % renderer->height, rand() % 10, { 255, 0, 255, 0 });
        //}*/
        //for (int i = 0; i < 3; i++)
        //{
        //    framebuffer->DrawQuadraticCurve(
        //        rand() % renderer->width, rand() % renderer->height,
        //        rand() % renderer->width, rand() % renderer->height,
        //        rand() % renderer->width, rand() % renderer->height, 30, { 255, 255, 0, 255 });
        //}
        //for (int i = 0; i < 3; i++)
        //{
        //    framebuffer->DrawCubicCurve(
        //        rand() % renderer->width, rand() % renderer->height,
        //        rand() % renderer->width, rand() % renderer->height,
        //        rand() % renderer->width, rand() % renderer->height,
        //        rand() % renderer->width, rand() % renderer->height,
        //        30, { 0, 255, 255, 255 });
        //}

        //nPostProcess::Invert(framebuffer->colorBuffer);
        //nPostProcess::Monochrome(framebuffer->colorBuffer);
        //nPostProcess::Noise(framebuffer->colorBuffer, 30);

        std::unique_ptr<Image> image = std::make_unique<Image>();

        image->Load("../resources/flower.bmp");
        image->Flip();

        std::unique_ptr<Image> image1 = std::make_unique<Image>(*image.get());
        nPostProcess::BoxBlur(image1->colorBuffer);
        framebuffer->DrawImage(0, 300, image1.get());

        std::unique_ptr<Image> image2 = std::make_unique<Image>(*image.get());
        nPostProcess::GaussianBlur(image2->colorBuffer);
        framebuffer->DrawImage(250, 300, image2.get());

        std::unique_ptr<Image> image3 = std::make_unique<Image>(*image.get());
        nPostProcess::Sharpen(image3->colorBuffer);
        framebuffer->DrawImage(500, 300, image3.get());

        framebuffer->DrawImage(30, 30, image.get());

		framebuffer->Update();
		renderer->CopyBuffer(framebuffer.get());

		renderer->Present();

        // Keeps the circle from breaking everything
        /*char s{ 'S' };
        std::cin >> s;*/
	}

	SDL_Quit();

	return 0;
}
