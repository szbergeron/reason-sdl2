
// Provides: caml_glClearColor
function caml_glClearColor(r, g, b, a) {
    joo_global_object.gl.clearColor(r, g, b, a);
    joo_global_object.gl.clear(joo_global_object.gl.COLOR_BUFFER_BIT);
}

// Provides: caml_glViewport
function caml_glViewport(x, y, width, height) {
    joo_global_object.gl.viewport(x, y , width, height);
}

// Provides: caml_glScissor
function caml_glScissor(x, y, width, height) {
    joo_global_object.gl.scissor(x, y , width, height);
}

// Provides: caml_glClearDepth
function caml_glClearDepth(d) {
    joo_global_object.gl.clearDepth(d);
    joo_global_object.gl.clear(joo_global_object.gl.DEPTH_BUFFER_BIT);
}

// Provides: caml_glGetString
function caml_glGetString() {
    return caml_js_to_string("Not implemented");
}

// Provides: caml_glAttachShader
function caml_glAttachShader(program, shader) {
    joo_global_object.gl.attachShader(program, shader);
}

// Provides: caml_glBindBuffer
function caml_glBindBuffer(target, buffer) {
    // TODO: target param
    var bufferType = joo_global_object.variantToBufferType[target];
    joo_global_object.gl.bindBuffer(bufferType, buffer)
}

// Provides: caml_glBufferData
function caml_glBufferData(target, data, usage) {
    // TODO: Remove size
    var bufferType = joo_global_object.variantToBufferType[target];
    joo_global_object.gl.bufferData(bufferType, data.data,  joo_global_object.gl.STATIC_DRAW)
}

// Provides: caml_glCompileShader
// Requires: caml_js_to_string
function caml_glCompileShader(shader) {
    joo_global_object.gl.compileShader(shader);

    var result = joo_global_object.gl.getShaderParameter(shader, joo_global_object.gl.COMPILE_STATUS);

    if (result) {
        return 0;
    } else {
        var log = joo_global_object.gl.getShaderInfoLog(shader);
        return [0, caml_js_to_string(log)];
    }
}

// Provides: caml_glCreateBuffer
function caml_glCreateBuffer() {
    return joo_global_object.gl.createBuffer();
}

// Provides: caml_glCreateProgram
function caml_glCreateProgram() {
    return joo_global_object.gl.createProgram();
}

// Provides: caml_glCreateShader
function caml_glCreateShader(type) {
    var glType;
    switch (type) {
        case 0:
            glType = joo_global_object.gl.VERTEX_SHADER;
            break;
        case 1:
            glType = joo_global_object.gl.FRAGMENT_SHADER;
            break;
        default:
            throw "Unrecognized shader type";
    }
    return joo_global_object.gl.createShader(glType);
}

// Provides: caml_glDepthFunc
function caml_glDepthFunc(df) {
    // TODO: Use df parameter
    joo_global_object.gl.depthFunc(joo_global_object.gl.LEQUAL);
}

// Provides: caml_glBlendFunc
function caml_glBlendFunc(src, dest) {
    joo_global_object.gl.blendFunc(joo_global_object.variantToBlendFunc[src], joo_global_object.variantToBlendFunc[dest]);
}

// Provides: caml_glDrawArrays
function caml_glDrawArrays(vDrawMode, first, count) {
    var drawMode = joo_global_object.variantToDrawMode[vDrawMode];
    joo_global_object.gl.drawArrays(drawMode, first, count);
}

// Provides: caml_glDrawElements
function caml_glDrawElements(vDrawMode, count, vDataType, first) {
    var drawMode = joo_global_object.variantToDrawMode[vDrawMode];
    var dataType = joo_global_object.variantToType[vDataType];
    joo_global_object.gl.drawElements(drawMode, count, dataType, first);
}

// Provides: caml_glEnable
function caml_glEnable(option) {
    var enableOption = joo_global_object.variantToEnableOption[option];
    joo_global_object.gl.enable(enableOption);
}

// Provides: caml_glDisable
function caml_glDisable(option) {
    var enableOption = joo_global_object.variantToEnableOption[option];
    joo_global_object.gl.disable(enableOption);
}

// Provides: caml_glLinkProgram
// Requires: caml_js_to_string
function caml_glLinkProgram(program) {
    joo_global_object.gl.linkProgram(program);

    var result = joo_global_object.gl.getProgramParameter(program, joo_global_object.gl.LINK_STATUS);

    if (result) {
        return 0;
    } else {
        var log = joo_global_object.gl.getProgramInfoLog(program);
        return [0, caml_js_to_string(log)];
    }
}

// Provides: caml_glGetAttribLocation
function caml_glGetAttribLocation(program, attribName) {
    return joo_global_object.gl.getAttribLocation(program, attribName)
}

// Provides: caml_glGetUniformLocation
function caml_glGetUniformLocation(program, uniformName) {
    return joo_global_object.gl.getUniformLocation(program, uniformName)
}

// Provides: caml_glUniform1f_byte
function caml_glUniform1f_byte(uniformLocation, f0) {
    return joo_global_object.gl.uniform1f(uniformLocation, f0);
}

// Provides: caml_glUniform2f_byte
function caml_glUniform2f_byte(uniformLocation, f0, f1) {
    return joo_global_object.gl.uniform2f(uniformLocation, f0, f1);
}

// Provides: caml_glUniform3f_byte
function caml_glUniform3f_byte(uniformLocation, f0, f1, f2) {
    return joo_global_object.gl.uniform3f(uniformLocation, f0, f1, f2);
}

// Provides: caml_glUniform4f_byte
function caml_glUniform4f_byte(uniformLocation, f0, f1, f2, f3) {
    return joo_global_object.gl.uniform4f(uniformLocation, f0, f1, f2, f3);
}

// Provides: caml_glUniform1i
function caml_glUniform1i(uniformLocation, f0) {
    return joo_global_object.gl.uniform1i(uniformLocation, f0);
}

// Provides: caml_glUniform2i
function caml_glUniform2i(uniformLocation, f0, f1) {
    return joo_global_object.gl.uniform2i(uniformLocation, f0, f1);
}

// Provides: caml_glUniform3i
function caml_glUniform3i(uniformLocation, f0, f1, f2) {
    return joo_global_object.gl.uniform3i(uniformLocation, f0, f1, f2);
}

// Provides: caml_glUniform4i
function caml_glUniform4i(uniformLocation, f0, f1, f2, f3) {
    return joo_global_object.gl.uniform4i(uniformLocation, f0, f1, f2, f3);
}

// Provides: caml_glUniform2fv
function caml_glUniform2fv(uniformLocation, v) {
    return joo_global_object.gl.uniform2fv(uniformLocation, v);
}

// Provides: caml_glUniform3fv
function caml_glUniform3fv(uniformLocation, v) {
    return joo_global_object.gl.uniform3fv(uniformLocation, v);
}

// Provides: caml_glUniform4fv
function caml_glUniform4fv(uniformLocation, v) {
    return joo_global_object.gl.uniform4fv(uniformLocation, v);
}

// Provides: caml_glUniformMatrix4fv
function caml_glUniformMatrix4fv(uniformLocation, uniformValue) {
    return joo_global_object.gl.uniformMatrix4fv(uniformLocation, false, uniformValue);
}

// Provides: caml_glShaderSource
function caml_glShaderSource(shader, src) {
    joo_global_object.gl.shaderSource(shader, src);
}

// Provides: caml_glUseProgram
function caml_glUseProgram(program) {
    joo_global_object.gl.useProgram(program);
}

// Provides: caml_glCreateTexture
function caml_glCreateTexture() {
    return joo_global_object.gl.createTexture();
}

// Provides: caml_glPixelStorei
function caml_glPixelStorei(param, val) {
    var pixelAlignment = joo_global_object.variantToPixelAlignmentParameter[param];

    return joo_global_object.gl.pixelStorei(pixelAlignment, val);
}

// Provides: caml_glBindTexture
function caml_glBindTexture(vTextureType, vTexture) {
    var textureType = joo_global_object.variantToTextureType[vTextureType];
    joo_global_object.gl.bindTexture(textureType, vTexture);
}

// Provides: caml_glTexParameteri
function caml_glTexParameteri(vTextureType, vTextureParameter, vTextureParameterValue) {
    var textureType = joo_global_object.variantToTextureType[vTextureType];
    var textureParameter = joo_global_object.variantToTextureParameter[vTextureParameter];
    var textureParameterValue = joo_global_object.variantToTextureParameterValue[vTextureParameterValue];

    joo_global_object.gl.texParameteri(textureType, textureParameter, textureParameterValue);
}

// Provides: caml_glTexImage2D_bytecode
function caml_glTexImage2D_bytecode(vTextureType, vLevel, vInternalFormat, vFormat, vType, vPixels) {
    var textureType = joo_global_object.variantToTextureType[vTextureType];
    var internalFormat = joo_global_object.variantToFormat[vInternalFormat];
    var format = joo_global_object.variantToFormat[vFormat];
    var type = joo_global_object.variantToType[vType];
    var numChannels = joo_global_object.formatToNumChannels[format];
    var width = vPixels.nth_dim(1) / numChannels;
    var height = vPixels.nth_dim(0);
    var pixels = vPixels.data;

    joo_global_object.gl.texImage2D(textureType, vLevel, internalFormat, width, height, 0, format, type, pixels);
}

// Provides: caml_glGenerateMipmap
function caml_glGenerateMipmap(vTextureType) {
    var textureType = joo_global_object.variantToTextureType[vTextureType];
    joo_global_object.gl.generateMipmap(textureType)
}

// Provides: caml_glVertexAttribPointer
function caml_glVertexAttribPointer(attributeLocation, numComponents) {
    // TODO: PARAMS!
    joo_global_object.gl.vertexAttribPointer(attributeLocation, numComponents, joo_global_object.gl.FLOAT, false, 0, 0);
}

// Provides: caml_glEnableVertexAttribArray
function caml_glEnableVertexAttribArray(attributeLocation) {
    joo_global_object.gl.enableVertexAttribArray(attributeLocation);
}

// Provides: caml_glReadPixels
function caml_glReadPixels(x, y, vFormat, vType, vPixels) {
  var format, type, numChannels;

  var format = joo_global_object.variantToFormat[vFormat];
  var numChannels = joo_global_object.formatToNumChannels[format];
  var type = joo_global_object.variantToType[vType];

  if (format === joo_global_object.gl.RGB) {
    joo_global_object.console.log("Warning: Your browser most likely doesn't support GL_RGB. Try GL_RGBA if you see an error");
  }

  var width = vPixels.nth_dim(1) / numChannels;
  var height = vPixels.nth_dim(0);
  var pixels = vPixels.data;
  joo_global_object.gl.readPixels(x, y, width, height, format, type, pixels);

  // If we're on a little-endian system, the R/B channels are swapped
  // So let's determine endianness...
  var marker = new joo_global_object.ArrayBuffer(4);
  var u32view = new joo_global_object.Uint32Array(marker);
  u32view[0] = 0x12345678;
  var u8view = new joo_global_object.Uint8Array(marker);
  if (u8view[0] == 0x78 && type == joo_global_object.gl.UNSIGNED_BYTE) {
    // We are little-endian. Onto the swap...
    for (var i = 0; i < width * height * numChannels; i += numChannels) {
      var tmp = pixels[i];
      pixels[i] = pixels[i+2];
      pixels[i+2] = tmp;
    }
  }
}

