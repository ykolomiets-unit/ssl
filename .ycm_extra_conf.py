def FlagsForFile( filename, **kwargs):
    return {
        'flags': [
            '-x',
            'c',
            '-Wall',
            '-Wextra',
            '-Werror',
			'-I./includes',
			'-I./lib/libft/includes',
			],
    }
