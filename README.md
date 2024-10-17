# CppNotebook
Notes from beginner to advance and examples regarding C++ and related.

* [Notebooks](/Notebook/README.md) - Here are the Notebook pages

* [Code](/Code/README.md) - Here are code samples, examples and exercise solutions.

<br>

<br>

### Markdown and GitHub style support

Supported style tools by markdown and github:

1. **Mermaid Diagrams**

    Supported for rendering flowcharts, sequence diagrams, Gantt charts, etc. (added in 2022).
    Example:

    ```mermaid
        graph TD;
            A-->B;
            A-->C;
            B-->D;
            C-->D;
    ```

2. **Task Lists**

    Allows the creation of checkboxes.
    Example:
    - [x] Task 1
    - [ ] Task 2

3. **Emoji Support**

    GitHub supports emojis natively using :emoji_name: syntax.
    Example:<br>
    🚀 This is a rocket emoji

4. **Footnotes**

    Create footnotes using [^1] and footnote references at the bottom.
    Example:

    Here is a simple footnote[^1]. With some additional text after it.

    [^1]: google.com


5. **Tables**

    Markdown tables are supported.
    Example:

    | Header 1 | Header 2 |
    | -------- | -------- |
    | Row 1    | Data 1   |
    | Row 2    | Data 2   |


6. Code Syntax Highlighting

    Supports fenced code blocks with language-specific syntax highlighting.
    Example:
    <br>**python**
    ```python
    def greet(name):
        return f"Hello, {name}!"

    print(greet("World"))
    ```
    **C++**
    ```cpp
    #include <iostream>
    using namespace std;
    int main() {
        cout << "Hello, World!" << endl;
        return 0;
    }
    ```
    **bash**
    ```bash
    #!/bin/bash
    echo "Hello, World!"
    ```

7. LaTeX Mathematical Notation

    Example: 

    1. 
        <br>The formula for the area of a circle is $A = \pi r^2$.
    


    