#pragma once

#ifndef INPUTCLASS_H
#define INPUTCLASS_H

class inputClass
{
	public:
		inputClass();
		inputClass(const inputClass& other);
		~inputClass();

		void initialize();

		bool isKeyDown(unsigned int keyID);
		void keyDown(unsigned int keyID);
		void keyUp(unsigned int keyID);

	private:

		bool keys[256];
};

#endif