#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

class InputHandler {
private:
	InputHandler() {}

	const Uint8* key_state;

	bool is_key_down(SDL_Scancode key);

public:
	static InputHandler& instance() {
		static InputHandler input_handler_instance;
		return input_handler_instance;
	}

	void update();
	void clean();

	~InputHandler() {}

};

#endif
