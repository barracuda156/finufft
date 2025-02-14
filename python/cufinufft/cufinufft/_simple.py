from cufinufft import Plan

def nufft1d1(x, data, n_modes=None, out=None, eps=1e-6, isign=1):
    return _invoke_plan(1, 1, x, None, None, data, out, isign, eps, n_modes)

def nufft1d2(x, data, out=None, eps=1e-6, isign=-1):
    return _invoke_plan(1, 2, x, None, None, data, out, isign, eps)

def nufft2d1(x, y, data, n_modes=None, out=None, eps=1e-6, isign=1):
    return _invoke_plan(2, 1, x, y, None, data, out, isign, eps, n_modes)

def nufft2d2(x, y, data, out=None, eps=1e-6, isign=-1):
    return _invoke_plan(2, 2, x, y, None, data, out, isign, eps)

def nufft3d1(x, y, z, data, n_modes=None, out=None, eps=1e-6, isign=1):
    return _invoke_plan(3, 1, x, y, z, data, out, isign, eps, n_modes)

def nufft3d2(x, y, z, data, out=None, eps=1e-6, isign=-1):
    return _invoke_plan(3, 2, x, y, z, data, out, isign, eps)

def _invoke_plan(dim, nufft_type, x, y, z, data, out, isign, eps, n_modes=None):
    dtype = data.dtype

    n_trans = _get_ntrans(dim, nufft_type, data)

    if nufft_type == 1 and out is not None:
        n_modes = out.shape[-dim:]
    if nufft_type == 2:
        n_modes = data.shape[-dim:]

    plan = Plan(nufft_type, n_modes, n_trans, eps, isign, dtype)

    plan.setpts(x, y, z)

    if out is None:
        out = plan.execute(data)
    else:
        plan.execute(data, out=out)

    return out


def _get_ntrans(dim, nufft_type, data):
    if nufft_type == 1:
        expect_dim = 1
    else:
        expect_dim = dim

    if data.ndim == expect_dim:
        n_trans = 1
    else:
        n_trans = data.shape[0]

    return n_trans
