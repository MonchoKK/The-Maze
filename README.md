# 🎮 3D Raycasting Game

## Introduction
Welcome to my 3D Raycasting Game, a project that started as a simple challenge to implement the classic **raycasting** technique used in early 3D games like Wolfenstein 3D. I had no prior experience with 3D rendering, but I wanted to dive into the world of graphics programming and learn how 3D games were made before modern graphics engines existed.

### The Journey
This project took me on a thrilling ride through the history of game development, where I learned not only about how raycasting works but also about the intricacies of SDL2, linear algebra, and optimizing for performance. Along the way, I faced challenges in implementing accurate wall rendering, managing memory efficiently, and ensuring smooth gameplay even on older hardware.


This was **not** an easy project. There were times I struggled with understanding the math behind raycasting, and the countless hours I spent debugging rendering issues left me frustrated more than once. But pushing through those challenges is what made the final product so rewarding. Now, I can proudly say I built a functioning 3D game from scratch!

### What I Learned & What's Next
The biggest lesson for me was that **trial and error** is a part of every development process. Every time I fixed a bug or found a performance bottleneck, I felt closer to mastering a new skill. In the next iteration of this project, I hope to add:
- **Textured walls and floors** to make the game more visually appealing
- **Enemy AI** to introduce a more dynamic and challenging experience
- A more complex map with interactive elements like doors and keys

You can read my full blog post on the process [here](https://www.linkedin.com/posts/kabelo-moncho-02118a1b4_creating-a-3d-raycasting-game-purpose-the-activity-7242097012563730432-mj5o?utm_source=share&utm_medium=member_desktop).

## Technical Deep Dive 🛠️
Raycasting is a rendering technique that projects rays from the player’s point of view and calculates the distance to the first object it hits. By using these distances, we can simulate a 3D environment in a 2D plane. Here's how I approached it:

1. **Casting Rays**: For each column of pixels on the screen, I cast a ray at a different angle and calculated where it intersected with the walls of the map.
2. **Wall Heights**: Once a wall is hit, I calculate its distance and render a vertical slice of the wall on the screen. The closer the wall, the taller it appears.
3. **Handling Edge Cases**: One of the hardest parts was dealing with edge cases where rays would "miss" walls due to floating-point precision errors.

Every line of code was carefully designed to ensure performance and accuracy. To maintain readability and avoid global variables, I structured my code into small functions, each responsible for a single task, and avoided exceeding 70 characters per line to pass Betty checks.

## Installation
Follow these steps to get the game running on your machine:

1. Clone the repository:
    ```bash
    git clone https://github.com/your-username/3d-raycasting-game.git
    cd 3d-raycasting-game
    ```
2. Install dependencies (SDL2):
    ```bash
    sudo apt-get install libsdl2-dev
    ```
3. Compile the game:
    ```bash
    gcc -Wall -Werror -Wextra -pedantic src/*.c -o raycasting-game -lSDL2
    ```
4. Run the game:
    ```bash
    ./raycasting-game
    ```

## Usage 🚀
Once the game is running, you can use the following controls:
- `W` to move forward
- `S` to move backward
- `A` to rotate left
- `D` to rotate right

You can modify the map directly in the code to create new levels or challenges.

## Contributions
I welcome all contributions! If you have ideas for improvements or want to help with the next iteration, feel free to open an issue or submit a pull request. You can:
1. Fork the repository
2. Create a new branch:
    ```bash
    git checkout -b feature-branch
    ```
3. Make your changes and commit:
    ```bash
    git commit -m "Add new feature"
    ```
4. Push to your branch and submit a PR.



## License 📄
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more information.

---

Thank you for checking out my project! I hope you enjoy playing it as much as I enjoyed building it. If you'd like to follow my journey, connect with me on [LinkedIn](https://www.linkedin.com/in/kabelo-moncho-02118a1b4?lipi=urn%3Ali%3Apage%3Ad_flagship3_profile_view_base_contact_details%3BSVKGuJkbTLa7OUTcoTayxA%3D%3D).

