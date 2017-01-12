#pragma once
#include <string>

class Display
{
public:
	
	~Display(){}
	
	std::string GetTitle() const;
	int GetWidth() const;
	int GetHeight() const;

	void SetVSync(bool vsync);
	bool GetVSync() const;

	void Clear();

	virtual void Init() = 0;
	virtual void SetTitle(std::string & title) = 0;
	virtual void SwapBuffers() = 0;
protected:
	Display(int width, int height, std::string &title);
private:
	int _width;
	int _height;
	bool _vsync;
	std::string _title;
};