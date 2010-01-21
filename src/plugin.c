/*
 * This file is part of spop.
 *
 * spop is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * spop is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * spop. If not, see <http://www.gnu.org/licenses/>.
 */

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

#include "spop.h"
#include "plugin.h"

audio_delivery_func_ptr g_audio_delivery_func = NULL;

void init_plugins() {
    void* lib_audio;
    char* error;

    /* Load audio plugin -- only OSS at the moment */
    lib_audio = dlopen("libspop_oss.so", RTLD_LAZY);
    if (!lib_audio) {
        fprintf(stderr, "Can't load audio plugin: %s\n", dlerror());
        exit(1);
    }
    dlerror(); /* Clear any existing error */
    g_audio_delivery_func = dlsym(lib_audio, "audio_delivery");
    if ((error = dlerror()) != NULL) {
        fprintf(stderr, "Can't find symbol in audio plugin: %s\n", error);
        exit(1);
    }
}