#!/bin/bash

# Function to set up AoC prompt with vibrant colors
setup_aoc_prompt() {
    # Set up a colorful AoC prompt with a cool expanded format
    export PS1="\[\033[1;36m\]AoC \[\033[0;35m\]\u@\h \[\033[0;32m\]\w \[\033[0;33m\]>\[\033[00m\] "  
    # Explanation:
    # - \033[1;36m: Cyan for "AoC"
    # - \033[0;35m: Magenta for user@hostname
    # - \033[0;32m: Green for the current directory
    # - \033[0;33m: Yellow for the prompt symbol (>)
    # - \033[00m: Reset colors after the prompt

    # Add ./bin to the PATH if it's not already there
    if [[ ":$PATH:" != *":$PWD/bin:"* ]]; then
        export PATH="$PWD/bin:$PATH"
    fi

    # Notify that AoC prompt is active
    echo -e "\033[1;32mAoC prompt set. 'exit' to return to normal shell.\033[0m"
}

# Function to restore the normal shell prompt
restore_normal_prompt() {
    export PS1="\[\033[01;32m\]\u@\h:\w\$ \[\033[00m\]"  # Default green prompt with user and directory
    echo -e "\033[1;32mNormal shell prompt restored.\033[0m"
}

# Run the setup for AoC
setup_aoc_prompt

# Define a custom exit function that restores the prompt
exit_aoc() {
    restore_normal_prompt
    exit 0
}

# Override the exit command to use the custom exit function
alias exit="exit_aoc"
